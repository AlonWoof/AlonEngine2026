#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "input.h"

extern float gDeltaTime;
extern GLFWwindow* gWindow;

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;



enum CameraMode
{
    CAMMD_NONE,
    CAMMD_FREE
};

class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;

    CameraMode mode;


    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }


    void Update()
    {
        switch (mode)
        {
            case CAMMD_NONE:
                break;

            case CAMMD_FREE:
                freeCamUpdate();
                break;

            default:
                break;
        }

        debugInput();
    }

    void debugInput()
    {
        if (inputKeyPressed(GLFW_KEY_F11))
        {
            if (mode == CAMMD_FREE)
            {
                mode = CAMMD_NONE;
            }
            else
            { 
                mode = CAMMD_FREE; 
            }
                
        }
    }

    void freeCamUpdate()
    {
        if (abs(gGamePad.leftStickX) > 0.1f || abs(gGamePad.leftStickY) > 0.1f)
        {
            glm::vec3 moveVec;
            moveVec = (Right * gGamePad.leftStickX) + (Front * gGamePad.leftStickY);
            moveVec *= (8.0f * gDeltaTime);

            Position += moveVec;
        }


        Yaw += gGamePad.mouseX * 0.15f;
        Pitch += gGamePad.mouseY * 0.2f;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        updateCameraVectors();
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

enum Buttons
{
	BUTTONS_NONE = 0,
	BUTTONS_A = 0x1,
	BUTTONS_B = 0x2,
	BUTTONS_X = 0x4,
	BUTTONS_Y = 0x8
};

typedef struct
{
	float leftStickX, leftStickY;
	float rightStickX, rightStickY;

	float mouseX, mouseY;
}  GamePad;

extern GamePad gGamePad;

void setupInput();
void inputProcess();
void inputMouseCallback(GLFWwindow* window, double xposIn, double yposIn);




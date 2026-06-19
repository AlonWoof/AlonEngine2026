#pragma once
#ifndef _GFX_H_
#define _GFX_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "texture.h"
#include "material.h"

bool initGFX();
void gfxRender();

// settings
typedef struct 
{
	unsigned int resX;
	unsigned int resY;
} ScreenSettings;

extern ScreenSettings gScreenSettings;
extern glm::mat4 gProjectionMatrix;
extern glm::mat4 gViewMatrix;
extern GLFWwindow* gWindow;
extern Camera gCamera;
extern float gDeltaTime;



#endif // !_GFX_H_

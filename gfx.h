#pragma once
#ifndef _GFX_H_
#define _GFX_H_

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


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

extern Light gDirLight;
extern glm::vec3 gAmbientLight;
extern Texture gDefaultTexture;


#endif // !_GFX_H_

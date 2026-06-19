
#include "gfx.h"
#include "camera.h"
#include "object.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


ScreenSettings gScreenSettings;
GLFWwindow* gWindow;
Camera gCamera;
glm::mat4 gProjectionMatrix;
glm::mat4 gViewMatrix;

static void fbSizeCallback(GLFWwindow* window, int width, int height);
extern bool gApplicationQuit;
extern std::vector<Object*> gObjectList;

bool initGFX()
{
	gScreenSettings.resX = 1280;
	gScreenSettings.resY = 720;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	gWindow = glfwCreateWindow(gScreenSettings.resX, gScreenSettings.resY, "AlonEngine 2026", NULL, NULL);

	if (gWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);
	glfwSetFramebufferSizeCallback(gWindow, fbSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

void fbSizeCallback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

extern Object* testObject;

void gfxRender()
{
	if (glfwWindowShouldClose(gWindow))
		gApplicationQuit = true;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gProjectionMatrix = glm::mat4(1.0f);
	//gViewMatrix = glm::mat4(1.0f);
	gProjectionMatrix = glm::perspective(glm::radians(60.0f), (float)gScreenSettings.resX / (float)gScreenSettings.resY, 0.1f, 100.0f);
	gViewMatrix = gCamera.GetViewMatrix();

	for (unsigned int i = 0; i < gObjectList.size(); i++)
	{
		gObjectList[i]->Draw();
	}

	glfwSwapBuffers(gWindow);
	glfwPollEvents();
}
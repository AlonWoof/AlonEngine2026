
#include "gfx.h"
#include "input.h"
#include "objTestCube.h"
#include "objTestJenny.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

bool gApplicationQuit = false;

void mainLoop();

Object* testObject;
float gDeltaTime = 0.0f;
float lastFrame = 0.0f;

std::vector<Object*> gObjectList;

int main()
{

	if (!initGFX())
		return -1;

	std::cout << "And so... it begins yet again, at the end of time..." << std::endl;

	setupInput();

	gObjectList.push_back(new ObjectTestJenny(glm::vec3(0.0f,0.0f,-5.0f)));
	gObjectList.push_back(new ObjectTestCube(glm::vec3(10.0f, 0.0f, -5.0f)));
	gObjectList.push_back(new ObjectTestCube(glm::vec3(-8.0f, -5.5f, -8.0f)));
	gObjectList.push_back(new ObjectTestCube(glm::vec3(-5.0f, -0.5f, -12.0f)));

	Material testMat("./data/materials/test.mat");

	while (!gApplicationQuit)
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		gDeltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		mainLoop();
	}

	return 0;
}

void mainLoop()
{
	inputProcess();
	gCamera.Update();

	for (unsigned int i = 0; i < gObjectList.size(); i++)
	{
		gObjectList[i]->Update();
	}

	gfxRender();
}

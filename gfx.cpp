
#include "gfx.h"
#include "camera.h"
#include "object.h"
#include "light.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

Light gDirLight;
glm::vec3 gAmbientLight;

Texture gDefaultTexture;

unsigned char defaultTexData[]
{
	0xff, 0xff, 0xff, 0xff
};

static void fbSizeCallback(GLFWwindow* window, int width, int height);
extern bool gApplicationQuit;
extern std::vector<Object*> gObjectList;

void setupDefaultTextureData()
{
	glGenTextures(1, &gDefaultTexture.id);
	glBindTexture(GL_TEXTURE_2D, gDefaultTexture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, defaultTexData);
}

void initUI()
{
	float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::StyleColorsDark();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)
	
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(gWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	
}

void drawUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (unsigned int i = 0; i < gObjectList.size(); i++)
	{
		gObjectList[i]->DrawUI();
	}

	gCamera.DrawUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

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

	//Set default light
	gDirLight.Direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	gDirLight.Color = glm::vec3(1.0f, 0.98f, 0.9f);
	gAmbientLight = glm::vec3(0.25f, 0.25f, 0.3f);

	setupDefaultTextureData();
	initUI();

	gCamera.Position = glm::vec3(0.0f, 0.8f, -3.58f);
	//gCamera.Yaw = -114.44f;
	//gCamera.Pitch = -6.81f;

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

	drawUI();

	glfwSwapBuffers(gWindow);
	glfwPollEvents();
	
	
}


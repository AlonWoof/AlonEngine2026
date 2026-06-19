
#include "gfx.h"
#include "input.h"
#include <cmath>

GamePad gGamePad;
extern GLFWwindow* gWindow;

static bool firstMouse = true;
float lastX;// = SCR_WIDTH / 2.0f;
float lastY;// = SCR_HEIGHT / 2.0f;

void setupInput()
{
    lastX = gScreenSettings.resX / 2.0f;
    lastY = gScreenSettings.resX / 2.0f;

    glfwSetCursorPosCallback(gWindow, inputMouseCallback);
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void inputProcess()
{
	gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, 0.0f, 0.1f);
	gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, 0.0f, 0.1f);
	gGamePad.rightStickX = 0.0f;
	gGamePad.rightStickY = 0.0f;

    gGamePad.mouseX = std::lerp(gGamePad.mouseX, 0.0f, 0.1f);
    gGamePad.mouseY = std::lerp(gGamePad.mouseY, 0.0f, 0.1f);

    if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
        gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, 1.0f, 0.1f);
    if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
        gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, -1.0f, 0.1f);
    if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
        gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, -1.0f, 0.1f);
    if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
        gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, 1.0f, 0.1f);
}



void inputMouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    gGamePad.mouseX = std::lerp(gGamePad.mouseX, (float)(xpos - lastX),0.1f);
    gGamePad.mouseY = std::lerp(gGamePad.mouseY, (float)(lastY - ypos),0.1f); // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //std::cout << "mouseX: " << gGamePad.mouseX << " mouseY: " << gGamePad.mouseY << std::endl;
}
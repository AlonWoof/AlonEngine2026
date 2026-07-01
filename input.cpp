
#include "gfx.h"
#include "input.h"
#include <cmath>

GamePad gGamePad;
extern GLFWwindow* gWindow;

static bool firstMouse = true;
float lastX;// = SCR_WIDTH / 2.0f;
float lastY;// = SCR_HEIGHT / 2.0f;

bool currentKeys[GLFW_KEY_LAST];
bool lastKeys[GLFW_KEY_LAST];
static void updateKeyStates();

void setupInput()
{
    lastX = gScreenSettings.resX / 2.0f;
    lastY = gScreenSettings.resX / 2.0f;

    //glfwSetCursorPosCallback(gWindow, inputMouseCallback);
    //glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //lockCursor();
}
void lockCursor()
{
    glfwSetCursorPosCallback(gWindow, inputMouseCallback);
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void unlockCursor()
{
    glfwSetCursorPosCallback(gWindow, NULL);
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(gWindow, ImGui_ImplGlfw_CursorPosCallback);
}

void inputProcess()
{
    updateKeyStates();
	gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, 0.0f, 0.1f);
	gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, 0.0f, 0.1f);
	gGamePad.rightStickX = 0.0f;
	gGamePad.rightStickY = 0.0f;

    gGamePad.mouseX = std::lerp(gGamePad.mouseX, 0.0f, 0.1f);
    gGamePad.mouseY = std::lerp(gGamePad.mouseY, 0.0f, 0.1f);

    if (inputKeyHeld(GLFW_KEY_W))
        gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, 1.0f, 0.1f);
    if (inputKeyHeld(GLFW_KEY_S))
        gGamePad.leftStickY = std::lerp(gGamePad.leftStickY, -1.0f, 0.1f);
    if (inputKeyHeld(GLFW_KEY_A))
        gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, -1.0f, 0.1f);
    if (inputKeyHeld(GLFW_KEY_D))
        gGamePad.leftStickX = std::lerp(gGamePad.leftStickX, 1.0f, 0.1f);


    
}

static void updateKeyStates()
{ 
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        lastKeys[i] = currentKeys[i];
        currentKeys[i] = (glfwGetKey(gWindow, i) == GLFW_PRESS);
    }
}

bool inputKeyPressed(int key)
{
    return currentKeys[key] && !lastKeys[key];
}

bool inputKeyHeld(int key)
{
    return currentKeys[key] && lastKeys[key];
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
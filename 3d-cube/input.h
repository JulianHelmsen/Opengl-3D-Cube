#pragma once
#include <glfw/glfw3.h>
class input
{
public:
	static float getDeltaXPos();
	static float getDeltaYPos();
	static void setWindow(GLFWwindow* windowPtr);
	static bool isButtonPressed();
private:

};


#pragma once
#include <glfw/glfw3.h>
class input
{
public:

	static void getMouseDelta(float* x, float* y);
	static void setWindow(GLFWwindow* windowPtr);
	static bool isButtonPressed(int keycode);
private:

};


#include "input.h"

static bool s_mouse_delta_initialized = false;
static float s_prev_mouse_x = -1.0f;
static float s_prev_mouse_y = -1.0f;
static float s_delta_mouse_x = 0.0f;
static float s_delta_mouse_y = 0.0f;


static GLFWwindow* s_window;


void input::getMouseDelta(float* x, float* y) {
	if (!s_mouse_delta_initialized) {
		*x = 0.0f;
		*y = 0.0f;
		return;
	}

	*x = (float)s_delta_mouse_x;
	*y = (float)-s_delta_mouse_y;
	s_delta_mouse_x = 0.0f;
	s_delta_mouse_y = 0.0f;
}

void input::setWindow(GLFWwindow* windowPtr) {
	s_window = windowPtr;

	glfwSetCursorPosCallback(s_window, [](GLFWwindow* window, double xpos, double ypos) -> void {
		if (s_prev_mouse_x < 0.0f)
			s_mouse_delta_initialized = true;

		s_delta_mouse_x = (float)xpos - s_prev_mouse_x;
		s_delta_mouse_y = (float)ypos - s_prev_mouse_y;

		s_prev_mouse_x = (float) xpos;
		s_prev_mouse_y = (float) ypos;
		
	});
}
bool input::isButtonPressed(int keycode) {
	return glfwGetKey(s_window, keycode) == GLFW_PRESS;
}
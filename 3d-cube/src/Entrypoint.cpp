#include <stdio.h>
#include <GLFW/glfw3.h>

int main(const int argc, const char** argv) {
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(1020, 720, "Window", NULL, NULL);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();
	}


	return 0;

}

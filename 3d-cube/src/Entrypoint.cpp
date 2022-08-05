#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "app.h"


int main(const int argc, const char** argv) {
	printf("Hello World\n");

	if(!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "BigJ", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewInit();
	onInit();

	while (!glfwWindowShouldClose(window)) {
		onRender();
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}

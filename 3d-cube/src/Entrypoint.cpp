#include <stdio.h>
#include <GLFW/glfw3.h>

int main(const int argc, const char** argv) {
	printf("Hello World\n");

	if(!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "BigJ", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

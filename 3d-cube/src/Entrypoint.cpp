#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "app.h"


int main(const int argc, const char** argv) {
	printf("Hello World\n");

	if(!glfwInit()) return -1;

	const int width = 1920;
	const int height = 1080;
	GLFWwindow* window = glfwCreateWindow(width, height, "BigJ", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) -> void {
		onResize(w, h);
	});

	glfwMakeContextCurrent(window);
	glewInit();
	onInit(width, height);
	auto prev = std::chrono::high_resolution_clock::now();
	float accu_time = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		auto now = std::chrono::high_resolution_clock::now();
		float time_diff = 1e-6f * std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count();
		prev = now;
		onRender(accu_time += time_diff, time_diff);

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
}

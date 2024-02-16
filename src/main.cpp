#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.h"
#include "logger.h"

int main() {
	Logger* logger = new Logger();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Spark", NULL, NULL);

	if(!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init glad" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 60);

	Renderer* renderer = new Renderer();

	while(!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);

		// events
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}

		// rendering

		renderer->clearColor();

		glfwPollEvents();
	}
	glfwTerminate();
	delete renderer;
	delete logger;
	return 0;
}

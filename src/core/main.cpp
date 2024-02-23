#include <cstddef>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.h"
#include "shader.h"
#include "sprite.h"

int main() {
	if(!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	glViewport(0, 0, 800, 600);

	/* clang-format on */
	const char* shaderSource = "../src/core/graphics/shaders/triangle.glsl";
	Shader shader = Shader(shaderSource);

	Renderer2D renderer = Renderer2D(shader);
	Sprite* sprite = new Sprite(0.5f, 0.5f);

	while(!glfwWindowShouldClose(window)) {
		// events
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}

		// rendering
		renderer.render(sprite,
						{0.0f, 0.0f, 0.0f},
						{sprite->width, sprite->height});

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete sprite;
	glfwTerminate();
	return 0;
}

#include <cstddef>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "glm/ext/matrix_transform.hpp"
#include "renderer.h"
#include "shader.h"
#include "loader.h"

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

	// triangle vertices
	/* clang-format off */
    vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
    };
    vector<unsigned int> indices = {
        0, 1, 2
    };
	/* clang-format on */

	Loader* loader = new Loader();
	RawModel model = loader->loadToVAO(vertices, indices);

	glm::mat4 trans = glm::mat4(1.0f);

	const char* shaderSource = "../src/shaders/triangle.glsl";
	Shader shader = Shader(shaderSource);

	while(!glfwWindowShouldClose(window)) {
		// events
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		unsigned int loc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(trans));
		// rendering
		glBindVertexArray(model.getVaoID());
		glEnableVertexAttribArray(0);

		glDrawElements(GL_TRIANGLES,
					   model.getVertexCount(),
					   GL_UNSIGNED_INT,
					   0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete loader;
	glfwTerminate();
	return 0;
}

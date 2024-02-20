#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.h"
#include "shader.h"
#include "logger.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "raw_model.h"
#include "loader.h"

struct layout {
	GLuint vertices_start;
	GLint size;
	GLenum vertexDataType;
	GLboolean should_be_normalized;
	GLsizei stride;
	void* pointer;
};

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

	RawModel model = RawModel{1, 3};

	glViewport(0, 0, 800, 600);

	// triangle vertices
	/* clang-format off */
    float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2
    };
	/* clang-format on */

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	VertexBuffer vb = VertexBuffer(vertices, sizeof(vertices));
	IndexBuffer ib = IndexBuffer(indices, 3);

	glVertexAttribPointer(0,
						  3,
						  GL_FLOAT,
						  GL_FALSE,
						  3 * sizeof(float),
						  (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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
		// rendering
		glBindVertexArray(VAO);
		ib.bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

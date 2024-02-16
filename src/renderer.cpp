#include <glad/glad.h>
#include "renderer.h"
#include <iostream>

void Renderer::render() {
	std::cout << "Rendering" << std::endl;
}

void Renderer::clearColor() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

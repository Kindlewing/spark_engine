#include "renderer.h"

using glm::vec2;

Renderer2D::Renderer2D(Shader& shader) : shader{shader} {};

void Renderer2D::render(Sprite* sprite, glm::vec3 pos, glm::vec2 size) {
	clearColor();
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(sprite->spriteData.vaoID);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES,
				   sprite->spriteData.vertexCount,
				   GL_UNSIGNED_INT,
				   0);
}

void Renderer2D::clearColor() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

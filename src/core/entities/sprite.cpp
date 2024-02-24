#include "sprite.h"
#include <iostream>
#include <ostream>

Sprite::Sprite(float width, float height) {
	this->width = width;
	this->height = height;

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vaos.push_back(VAO);
	glBindVertexArray(VAO);
	this->vaoID = VAO;

	unsigned int IBO;
	vbos.push_back(IBO);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 indices.size() * sizeof(unsigned int),
				 std::data(indices),
				 GL_STATIC_DRAW);
	storeInAttribList(0, vertices);
	glBindVertexArray(0);
	this->vertexCount = indices.size();
}

Sprite::~Sprite() {
	std::cout << "Clean up sprite data" << std::endl;
	for(int i = 0; i < vaos.size(); i++) {
		GLuint vao = vaos.at(i);
		glDeleteVertexArrays(1, &vao);
	}

	for(int i = 0; i < vbos.size(); i++) {
		GLuint vbo = vbos.at(i);
		glDeleteBuffers(1, &vbo);
	}
}

void Sprite::storeInAttribList(int index, vector<float> vertices) {
	unsigned int VBO;
	vbos.push_back(VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
				 vertices.size() * sizeof(float),
				 std::data(vertices),
				 GL_STATIC_DRAW);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

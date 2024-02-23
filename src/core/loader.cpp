#include "loader.h"
#include <fcntl.h>
#include <iostream>
#include <strings.h>
#include <vector>

using std::vector;

Loader::~Loader() {
	std::cout << "Cleaning up loader GL data" << std::endl;
	for(int i = 0; i < vaos.size(); i++) {
		GLuint vao = vaos.at(i);
		glDeleteVertexArrays(1, &vao);
	}

	for(int i = 0; i < vbos.size(); i++) {
		GLuint vbo = vbos.at(i);
		glDeleteBuffers(1, &vbo);
	}
}
VertexData Loader::loadToVAO(vector<float> vertices,
							 vector<unsigned int> indices) {
	int vaoID = createVAO();
	bindIndexBuffer(indices);
	storeInAttribList(0, vertices);
	unbindVAO();
	return VertexData{vaoID, indices.size()};
}

unsigned int Loader::createVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vaos.push_back(VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void Loader::storeInAttribList(int index, vector<float> vertices) {
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

void Loader::bindIndexBuffer(vector<unsigned int> indices) {
	unsigned int IBO;
	vbos.push_back(IBO);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 indices.size() * sizeof(unsigned int),
				 std::data(indices),
				 GL_STATIC_DRAW);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

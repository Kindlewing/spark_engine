#include "loader.h"
#include "rawModel.h"

RawModel Loader::loadToVAO(void* data, unsigned int count) {
	int vaoID = createVAO();
	storeInAttribList(0, sizeof(data), data);
	unbindVAO();
	RawModel model = RawModel(vaoID, count);
	return model;
}

unsigned int Loader::createVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	vaos.push_back(VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void Loader::storeInAttribList(int index, GLsizeiptr size, void* data) {
	unsigned int VBO;
	vbos.push_back(VBO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
	glBindVertexArray(0);
}

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

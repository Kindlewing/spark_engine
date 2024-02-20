#include "index_buffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : count(count) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 count * sizeof(GLuint),
				 data,
				 GL_STATIC_DRAW);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

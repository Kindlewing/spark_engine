#include "vertex_array.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
}

void VertexArray::bind() {
	glBindVertexArray(ID);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

#pragma once

#include <glad/glad.h>
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
  public:
	VertexArray();
	void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void bind();
	void unbind();

  private:
	GLuint ID;
};

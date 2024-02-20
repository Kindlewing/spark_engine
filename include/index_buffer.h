#include <glad/glad.h>

class IndexBuffer {
  public:
	IndexBuffer(const void* data, unsigned int size);
	void bind();
	void unbind();

  private:
	unsigned int ID;
	GLuint count;
};

#include <glad/glad.h>

class VertexBuffer {
  public:
	VertexBuffer(const void* data, unsigned int size);
	void bind();
	void unbind();

  private:
	unsigned int ID;
};

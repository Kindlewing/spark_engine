#pragma once
#include <glad/glad.h>

class RawModel {
  public:
	RawModel(unsigned int vaoID, unsigned int vertexCount);
	unsigned int getVaoID();
	unsigned int getVertexCount();

  private:
	unsigned int vaoID;
	unsigned int vertexCount;
};

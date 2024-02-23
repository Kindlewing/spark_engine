#pragma once

#include <glad/glad.h>
#include <vector>

using std::vector;

struct VertexData {
	int vaoID;
	unsigned long vertexCount;
};

class Loader {
  public:
	~Loader();
	VertexData loadToVAO(vector<float> vertices, vector<unsigned int> indices);

  private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	unsigned int createVAO();
	void storeInAttribList(int index, vector<float> vertices);
	void bindIndexBuffer(vector<unsigned int> indices);
	void unbindVAO();
};

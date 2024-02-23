#pragma once

#include <glad/glad.h>
#include <vector>
#include "rawModel.h"
using std::vector;
class Loader {
  public:
	RawModel loadToVAO(vector<float> vertices, vector<unsigned int> indices);

  private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	unsigned int createVAO();
	void storeInAttribList(int index, vector<float> vertices);
	void bindIndexBuffer(vector<unsigned int> indices);
	void unbindVAO();
};

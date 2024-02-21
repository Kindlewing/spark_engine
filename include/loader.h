#pragma once

#include <glad/glad.h>
#include <vector>
#include "rawModel.h"

class Loader {
  public:
	RawModel loadToVAO(void* data, unsigned int count);

  private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	unsigned int createVAO();
	void storeInAttribList(int index, GLsizeiptr size, void* data);
	void unbindVAO();
};

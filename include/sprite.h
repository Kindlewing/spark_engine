#pragma once

#include <glad/glad.h>
#include <vector>

using std::vector;

class Sprite {
  public:
	float width, height;
	unsigned long vertexCount;
	int vaoID;
	Sprite(float width, float height);
	~Sprite();

  private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	void storeInAttribList(int index, vector<float> vertices);
	/* clang-format off */ 
	vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

    vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
    };
	/* clang-format on */
};

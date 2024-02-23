#pragma once

#include "loader.h"
#include <vector>

using std::vector;

class Sprite {
  public:
	float width, height;
	int id;
	VertexData spriteData;
	Sprite(float width, float height);
	~Sprite();

  private:
	Loader* loader;
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

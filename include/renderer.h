#pragma once
#include <glad/glad.h>
#include "glm/fwd.hpp"
#include "shader.h"
#include "sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer2D {
  public:
	Renderer2D(Shader& shader);
	void render(Sprite* sprite, glm::vec3 pos, glm::vec2 size);

  private:
	Shader& shader;
	void clearColor();
};

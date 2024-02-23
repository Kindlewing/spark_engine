#include "sprite.h"

Sprite::Sprite(float width, float height) {
	this->width = width;
	this->height = height;
	this->loader = new Loader();
	this->spriteData = loader->loadToVAO(this->vertices, this->indices);
}

Sprite::~Sprite() {
	delete this->loader;
}

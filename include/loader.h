#pragma once

#include <glad/glad.h>
#include <vector>
#include "raw_model.h"

RawModel loadToVAO(std::vector<float> positions);
unsigned int createVAO();
void storeInAttributeList(int attributeNumber, std::vector<float> data);
void unbindVAO();

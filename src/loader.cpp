#include "loader.h"
#include <vector>

RawModel loadToVAO(std::vector<float> positions) {
	int vaoID = createVAO();
	storeInAttributeList(0, positions);
	unbindVAO();
	return RawModel{vaoID, positions.size() / 3};
}

unsigned int createVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	return VAO;
}

void storeInAttributeList(int attributeNumber, std::vector<float> data) {
}

void unbindVAO() {
	glBindVertexArray(0);
}

#include "shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

using glm::mat4;
using std::size_t;

Shader::Shader(const char* source) {
	std::ifstream stream(source);
	std::stringstream ss[2];
	int mode = 0;
	std::string line;
	while(getline(stream, line)) {
		if(line.find("//shader") != std::string::npos &&
		   line.find("vertex") != std::string::npos) {
			// Vertex
			mode = 0;
		}

		if(line.find("//shader") != std::string::npos &&
		   line.find("fragment") != std::string::npos) {
			// fragment
			mode = 1;
		}
		ss[(int)mode] << line << "\n";
	}

	std::string vShaderCode = ss[0].str();
	std::string fShaderCode = ss[1].str();

	const char* src_v = vShaderCode.c_str();
	const char* src_f = fShaderCode.c_str();

	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &src_v, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &src_f, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer
	// necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::uploadTransformationMatrix(const string& name, mat4 mat) const {
	unsigned int loc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if(type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout
				<< "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
				<< infoLog
				<< "\n -- --------------------------------------------------- "
				   "-- "
				<< std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout
				<< "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
				<< infoLog
				<< "\n -- --------------------------------------------------- "
				   "-- "
				<< std::endl;
		}
	}
}

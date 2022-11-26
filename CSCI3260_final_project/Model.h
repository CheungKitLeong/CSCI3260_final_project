#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"

#include "Shader.h"

#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>


struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
};

class Model 
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	GLuint vaoID;

	Model(const char* path);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj, Shader shader);

private:

	// load model from path
	void loadOBJ(const char* objPath);
	// make VAO, VBO and EBO
	void constructVAO();

};
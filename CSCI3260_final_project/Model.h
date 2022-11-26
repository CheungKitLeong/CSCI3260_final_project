#pragma once
#include "Dependencies/glm/glm.hpp"

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

	Model(const char* path)
	{
		loadOBJ(path);
	}

private:

	// load model from path
	void loadOBJ(const char* objPath);

};
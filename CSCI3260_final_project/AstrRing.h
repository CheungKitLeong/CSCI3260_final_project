#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"


#include "Shader.h"
#include "Model.h"
#include "Shader.h"

#include <vector>
#include <queue>

#include <iostream>
//#include <string>
//#include <fstream>

/*
struct Rock {
	glm::vec3 size;
	glm::vec3 position;
};
*/

class AstrRing {
	
public:	
	
	int rockCount;
	std::queue<float> offsetxQueue;
	float ringRadius;
	//glm::vec3 center;

	AstrRing(int rock, float radius);

	void Render(Model* model, glm::mat4 center, glm::mat4 view, glm::mat4 proj, Shader shader);

	//void Render(int rockCount, float radius, glm::mat4 center);


};

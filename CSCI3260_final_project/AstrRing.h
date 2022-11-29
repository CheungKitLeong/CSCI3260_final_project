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


class AstrRing {
	
public:	
	
	int rockCount;
	std::queue<float> offsetxQueue;
	std::queue<float> offsetyQueue;
	std::queue<float> sizeQueue;
	std::queue<bool> zAxisQueue;

	float ringRadius;

	//Set rock count, and ring radius;
	AstrRing(int rock, float radius);

	void Render(Model* model, glm::mat4 center, glm::mat4 view, glm::mat4 proj, Shader shader);



};

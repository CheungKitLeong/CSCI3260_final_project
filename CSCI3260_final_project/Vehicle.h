#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"


#include "Shader.h"
#include "Model.h"
#include "AstrRing.h"

#include <vector>
#include <queue>

#include <iostream>

class Vehicle {
public:


	bool movingRight = false;
	float timer = 0;
	float leftTimer = 0;
	float rightTimer = -1;
	int cycle = 0;

	float vSpeed = 10.0f;
	float distance = 0;

	glm::vec4 vectorA = glm::vec4(1.0);
	glm::vec4 vectorB = glm::vec4(1.0);

	Vehicle();

	void Render(Model* vehicle, float speed, glm::mat4 vehicleTrans, glm::mat4 cameraObjTrans, glm::mat4 view, glm::mat4 proj, Shader shader);

	bool Collision(glm::vec4 vectorA, glm::vec4 vectorB);

};
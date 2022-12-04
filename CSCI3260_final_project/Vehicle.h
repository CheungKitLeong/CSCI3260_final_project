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
	float leftTimer = -timer * vSpeed;
	float rightTimer = -1;
	int cycle = 0;

	float vSpeed = 10.0f;
	float distance = 0;

	Vehicle();

	void Render(Model* vehicle, float speed, glm::mat4 vehicleTrans,  glm::mat4 view, glm::mat4 proj, Shader shader);

};
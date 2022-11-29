#include "AstrRing.h"
#include "Model.h"

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include <ctime>
#include <cstdlib>

using namespace std;


//#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

AstrRing::AstrRing(int rock, float radius) {
	rockCount = rock;
	ringRadius = radius;
	//queue<float> offsetxQueue;

	float sizeMax = 0.05;
	float sizeMin = 0.03;
	float yMax = 0.9;
	float yMin = 0.5;

		// * Generate a queue of random numbers for rendering before paintGL()*
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < rockCount; i++) {
		float offSetx = -ringRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * ringRadius)));
		std::cout << "First Offset x:" << offSetx;
		offsetxQueue.push(offSetx);

		float offSety = yMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (yMax - yMin)));
		std::cout << "First Offset x:" << offSetx;
		offsetyQueue.push(offSety);

		float size = sizeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (sizeMax)));
		sizeQueue.push(size);

		bool zAxis = rand()%2;
		zAxisQueue.push(zAxis);
	}

}


void AstrRing::Render(Model* model, glm::mat4 center, glm::mat4 view, glm::mat4 proj, Shader shader) {
	
	//for (int i = 0; i < rockCount; i++) {}

	queue<float> offsetxTemp = offsetxQueue;
	queue<float> offsetyTemp = offsetyQueue;
	queue<float> sizeTemp = sizeQueue;
	queue<bool> zAxisTemp = zAxisQueue;
		
	while(!offsetxTemp.empty()){

		float size = sizeTemp.front();

		float offSetx = offsetxTemp.front();
		float offSetz = sqrt(pow(ringRadius, 2) - pow(offSetx, 2));
		if (!zAxisTemp.front())
			offSetz = -offSetz;		//So that both positive and negative value of z offset can be obtained.
		float offSety = offsetyTemp.front();


		std::cout << "Offset x:" << offSetx << ", Offset z:" << offSetz << ";\n";

		glm::vec3 rockOffset = glm::vec3(offSetx, offSety, offSetz);
		glm::mat4 rockTrans = glm::translate(center, rockOffset);
		rockTrans = glm::scale(rockTrans, glm::vec3(size, size, size));
		model->draw(rockTrans, view, proj, shader);

		offsetxTemp.pop();
		offsetyTemp.pop();
		sizeTemp.pop();
		zAxisTemp.pop();
	}	

		/*
		//float offSetx = 0;
		//float offSety = 0;
		float offSetz = 0;

		//offSetx = -radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * radius)));
		offSetz = sqrt(pow(ringRadius,2) - pow(offSetx, 2));		//if RANDOM_BOOL = true, offSetz = -offSetz;

		std::cout << offSetx << "," << offSetz << ";\n";

		glm::vec3 rockOffset = glm::vec3(offSetx, 0.0f, offSetz);
		glm::mat4 rockTrans = glm::translate(center, rockOffset);
		rockTrans = glm::scale(rockTrans, glm::vec3(0.2, 0.2, 0.2));
		model->draw(rockTrans, view, proj, shader);
		*/
	
	

}


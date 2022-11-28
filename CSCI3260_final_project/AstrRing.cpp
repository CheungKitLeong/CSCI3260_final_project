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


	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < rockCount; i++) {
		float offSetx = -ringRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * ringRadius)));
		std::cout << "First Offset x:" << offSetx;
		offsetxQueue.push(offSetx);
	}

		


}


void AstrRing::Render(Model* model, glm::mat4 center, glm::mat4 view, glm::mat4 proj, Shader shader) {
	
	//for (int i = 0; i < rockCount; i++) {}

	queue<float> offsetxTemp = offsetxQueue;

		
	while(!offsetxTemp.empty()){
		float offSetx = offsetxTemp.front();
		float offSetz = sqrt(pow(ringRadius, 2) - pow(offSetx, 2));		//if RANDOM_BOOL = true, offSetz = -offSetz;

		std::cout << "Offset x:" << offSetx << ", Offset z:" << offSetz << ";\n";

		glm::vec3 rockOffset = glm::vec3(offSetx, 0.0f, offSetz);
		glm::mat4 rockTrans = glm::translate(center, rockOffset);
		rockTrans = glm::scale(rockTrans, glm::vec3(0.1, 0.1, 0.1));
		model->draw(rockTrans, view, proj, shader);

		offsetxTemp.pop();
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


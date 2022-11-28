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

AstrRing::AstrRing() {
	srand(static_cast <unsigned> (time(0)));

}


void AstrRing::Render(Model* model, glm::mat4 center, glm::mat4 view, glm::mat4 proj, Shader shader) {
	float radius = 5;

	float offSetx = 0;
	//float offSety = 0;
	float offSetz = 0;

	//srand(time(0));
	//offSetx = -radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (radius - (-radius))));

	offSetx = -radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * radius)));
	offSetz = sqrt(pow(radius,2) - pow(offSetx, 2));		//if RANDOM_BOOL = true, offSetz = -offSetz;

	std::cout << offSetx << "," << offSetz << ";\n";

	glm::vec3 rockOffset = glm::vec3(offSetx, 0.0f, offSetz);
	glm::mat4 rockTrans = glm::translate(center, rockOffset);
	rockTrans = glm::scale(rockTrans, glm::vec3(0.5, 0.5, 0.5));
	model->draw(rockTrans, view, proj, shader);

}


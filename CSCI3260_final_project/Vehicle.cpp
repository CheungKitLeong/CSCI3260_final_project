#include "Vehicle.h"
#include "Model.h"

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include <ctime>
#include <cstdlib>

using namespace std;

 Vehicle::Vehicle() {

}


void Vehicle::Render(Model* vehicle, glm::mat4 vehicleTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {

	timer = glfwGetTime() - 3;
//movingRight = false;
	leftTimer = -timer * vSpeed;
	//rightTimer = -1;

	vehicleTrans = glm::translate(vehicleTrans, glm::vec3(12.0f, 0.0f, -30.0f));

	if (leftTimer <= -25.0f)
		movingRight = true;
	std::cout << "Moveing Right? :" << movingRight << "\n";

	/**/
	if (rightTimer >= 0.0f) {
		movingRight = false;
		//leftTimer = timer * 5.0f + 120.0f;
		rightTimer = 0;
	}
	std::cout << "Moveing Right? :" << movingRight << "\n";
	

	if (!movingRight) {
		vehicleTrans = glm::translate(vehicleTrans, glm::vec3(leftTimer, 0.0f, 0.0f));
		//leftTimer = 0;
		std::cout << "Left Timer: " << leftTimer << "\n";
		std::cout << "Moveing Left!!!" << "\n";

	}
	else {
		//float tmpLeft = leftTimer;
		rightTimer = timer * vSpeed - 50.0f;
		//std::cout << rightTimer <<","<<tmpLeft << "\n";
		vehicleTrans = glm::translate(vehicleTrans, glm::vec3(rightTimer, 0.0f, 0.0f));
		std::cout << "Right Timer: " << rightTimer << "\n";
		std::cout << "Moveing Right!!!" << "\n";

	};

	vehicleTrans = glm::scale(vehicleTrans, glm::vec3(0.2f));

	vehicle->draw(vehicleTrans, view, proj, shader);

}
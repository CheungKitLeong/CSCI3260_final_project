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


void Vehicle::Render(Model* vehicle, float speed, glm::mat4 vehicleTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {

	vSpeed = speed;
	distance = 25.0f;

	timer = glfwGetTime() - 3;


		// When hiting the left boundary, turn to the right
	if (leftTimer <= -distance) {
		movingRight = true;
		cycle += 1;
		cout << "Cycle: " << cycle << "\n";
		leftTimer = 0;

	}
	std::cout << "Moveing Right? :" << movingRight << "\n";

	/**/
			// When hiting the right boundary, turn to the left
	if (rightTimer >= 0.0f) {
		movingRight = false;
		//leftTimer = timer * 5.0f + 120.0f;
		rightTimer = -1;
	}
	std::cout << "Moveing Right? :" << movingRight << "\n";
	

	if (!movingRight) {
		leftTimer = - timer * vSpeed + cycle * 2 * distance;
		vehicleTrans = glm::translate(vehicleTrans, glm::vec3(leftTimer, 0.0f, 0.0f));
		std::cout << "Left Timer: " << leftTimer << "\n";
		std::cout << "Moveing Left!!!" << "\n";

	}
	else {
		//float tmpLeft = leftTimer;
		rightTimer = timer * vSpeed - cycle * 2 * distance;
		//std::cout << rightTimer <<","<<tmpLeft << "\n";
		vehicleTrans = glm::translate(vehicleTrans, glm::vec3(rightTimer, 0.0f, 0.0f));
		std::cout << "Right Timer: " << rightTimer << "\n";
		std::cout << "Moveing Right!!!" << "\n";

	};

	vehicleTrans = glm::scale(vehicleTrans, glm::vec3(0.2f));

	vehicle->draw(vehicleTrans, view, proj, shader);

}
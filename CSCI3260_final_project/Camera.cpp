#include "Camera.h"

//#include "Dependencies/GLFW/glfw3.h"

//#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

/*
Camera::Camera()
{
	Position.x = speed * xPress;
}
*/

void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		xPress += 1;
		Position.x = speed * xPress;
	}
}

void Camera::ProcessMouseMovement_Left(double x) {
	/*
	if (mouseNeverMoved) {
		lastX = x;
		//lastY = y;
		mouseNeverMoved = false;
	}*/
	

	//std::cout << "Initial yaw and pitch: " << yaw << ";\n"; // << pitch << "\n";
	xoffset = x - lastX;
	//yoffset = lastY - y;

	lastX = x;
	//lastY = y;

	xoffset *= sensitivity;

	yaw += xoffset;

	//std::cout << "Final yaw: " << yaw << ";\n"; //<< pitch << "\n";
}

void Camera::Update() {
	Position.x = speed * xPress;
	Position.z = speed * zPress;

	Camera::ProcessMouseMovement_Left(rotation);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)); //* cos(glm::radians(pitch));
	direction.y = 0.0f; //sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)); //* cos(glm::radians(pitch));
	Orientation = glm::normalize(direction);


}



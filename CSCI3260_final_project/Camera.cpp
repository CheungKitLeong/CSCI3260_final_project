#include "Camera.h"
#include "Model.h"
#include "Shader.h"

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

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

void Camera::ProcessMouseMovement(double x) {
	/**/
	if (mouseNeverMoved) {
		lastX = x;
		//lastY = y;
		mouseNeverMoved = false;
	}
	

	//std::cout << "Initial yaw and pitch: " << yaw << ";\n"; // << pitch << "\n";
	xoffset = x - lastX;
	//yoffset = lastY - y;

	lastX = x;
	//lastY = y;

	xoffset *= sensitivity;

	yaw += xoffset;

	//std::cout << "Final yaw: " << yaw << ";\n"; //<< pitch << "\n";
}

void Camera::Object(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {

	glm::vec3 planeOffSet = glm::vec3(0.0f, -0.3f, 0.0f);
	modelTrans = glm::mat4(1.0f);
	modelTrans = glm::translate(modelTrans, Position + Orientation + planeOffSet);
	modelTrans = glm::rotate(modelTrans, glm::radians(-yaw + 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//TO DO: Rotate spacecraft along with camera
	modelTrans = glm::scale(modelTrans, glm::vec3(0.0005, 0.0005, 0.0005));
	object->draw(modelTrans, view, proj, shader);

}


void Camera::Update() {
	Position.x = speed * xPress;
	Position.z = speed * zPress;

	//Camera::ProcessMouseMovement(rotation);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)); //* cos(glm::radians(pitch));
	direction.y = 0.0f; //sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)); //* cos(glm::radians(pitch));
	Orientation = glm::normalize(direction);


}



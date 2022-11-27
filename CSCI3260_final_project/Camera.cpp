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

void Camera::Update() {
	Position.x = speed * xPress;

}



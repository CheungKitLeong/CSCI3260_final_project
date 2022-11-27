#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"

#include "Shader.h"

#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>#pragma once

class Camera
{
public:
	// Stores the main vectors of the camera
	float xPress = 0;
	float yPress = 0;
	float zPress = 0;

	float rSpeed = 0.5;
	float rotation = 0;

	float xoffset;
	//float yoffset;
	bool mouseNeverMoved = true;
	float lastX = 400;//, lastY = 300;
	float yaw, pitch = 0;
	const float sensitivity = 0.2f;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
			//***viewMatrix = glm::lookAt(Camera.Position, Camera.LookingPt, Camera.Up);

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.5f;
	//float sensitivity = 100.0f;


	// Camera constructor
	//Camera();



	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);

	//void ProcessMouseMovement_Left(double x, double y);
	void ProcessMouseMovement_Left(double x);

	void Update();

};

#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"

#include "Model.h"
#include "Shader.h"

//#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>#pragma once

class Camera
{
public:
	// * Horizontal movement variables
	float xPress = 0;
	float zPress = 0;
	float speed = 2.0f;

	// * Camera rotation variables
	bool mouseNotMoving = true;
	float lastX = 400;
	float yaw = -90;
	float sensitivity = 1.0f;

		// * New Camera Object variables
	glm::vec3 scInitialPos = glm::vec3(0);
	glm::vec3 scTranslation = glm::vec3(0.0f, -0.2f, -1.0f);
	glm::vec3 sc_local_pos = glm::vec3(0, 0, 0);  
	glm::vec3 sc_world_pos;

	glm::mat4 sc_trans_M = glm::mat4(1.0f);
	glm::mat4 sc_Rot_M = glm::mat4(1.0f);
	glm::mat4 sc_scale_M = glm::mat4(1.0f);
	float scale = 0.0005;

	glm::mat4 modelMatrix;
	glm::vec3 sc_local_front = glm::vec3(0, 0, -1.0f);	
	glm::vec3 sc_local_right = glm::vec3(1.0f, 0, 0);
	glm::vec4 sc_World_Front_Dir;
	glm::vec4 sc_World_Right_Dir;

	float oldx = 400;
	float viewRotateDegree = 0.0f;

		//***


	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
			
	//viewMatrix = glm::lookAt(Camera.Position, Camera.LookingPt, Camera.Up);

	// Camera constructor
	//Camera();

	// Updates and exports the camera matrix to the Vertex Shader
	//void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	
	void Object(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader);
	void ObjectNew(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader);

	// Handles camera inputs
	//void Inputs(GLFWwindow* window);

	void ProcessMouseMovement(double x);
	void PassiveMouse(int x, int y);

	void Update();
	void UpdateNew();

};

#include "Camera.h"
#include "Model.h"
#include "Shader.h"

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"


/*
Camera::Camera()
{
	Position.x = speed * xPress;
}
*/

/*
void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		xPress += 1;
		Position.x = speed * xPress;
	}
}
*/

// *** Process Mouse Movement for camera rotation
void Camera::ProcessMouseMovement(double x) {
	/**/

	if (mouseNotMoving) {
		lastX = x;
		mouseNotMoving = false;
	}

	//std::cout << "Initial yaw, x, lastx: " << yaw << " , "<< x <<", " << lastX << ";\n"; // << pitch << "\n";
	float xoffset = x - lastX;
	lastX = x;
	xoffset *= sensitivity;

	yaw += xoffset;
	//std::cout << "Final yaw, x, lastx: " << yaw << " , " << x << ", " << lastX << ";\n"; //<< pitch << "\n";
}

// *** Handle movement of the camera object (Spacecraft)
//		- fixed to the camera
void Camera::Object(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {

	glm::vec3 planeOffSet = glm::vec3(0.0f, -0.3f, 0.0f);
	modelTrans = glm::mat4(1.0f);
	modelTrans = glm::translate(modelTrans, Position + Orientation + planeOffSet);
	modelTrans = glm::rotate(modelTrans, glm::radians(-yaw + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelTrans = glm::scale(modelTrans, glm::vec3(0.0005, 0.0005, 0.0005));
	object->draw(modelTrans, view, proj, shader);

}

// *** Handle movement of the camera
void Camera::Update() {


	//Position += 0.1f * xPress * glm::normalize(glm::cross(Orientation, Up));
	//Position += 0.1f * xPress * Orientation;

	/**/
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)); //* cos(glm::radians(pitch));
	direction.y = 0.0f; //sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)); //* cos(glm::radians(pitch));
	Orientation = glm::normalize(direction);
	

	/* //Old ver.*/
	Position.x = speed * xPress;
	Position.z = speed * zPress;
	


	std::cout << "Direction x and z: " << Orientation.x << " , " << Orientation.z <<  ";\n"; //<< pitch << "\n";
	std::cout << "Position x and z: " << Position.x << " , " << Position.z << ";\n"; //<< pitch << "\n";
}










//*** New Experimenting codes

void Camera::ObjectNew(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {
	
	sc_scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	sc_trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(scInitialPos[0] + scTranslation[0], 
																	 scInitialPos[1] + scTranslation[1], 
																	 scInitialPos[2] + scTranslation[2])	);
	//sc_Rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(viewRotateDegree + 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	modelMatrix = sc_trans_M * sc_Rot_M * sc_scale_M;
	sc_world_pos = modelMatrix * glm::vec4(sc_local_pos, 1.0f);

	sc_World_Front_Dir = modelMatrix * glm::vec4(sc_local_front, 1.0f);
		sc_World_Front_Dir = glm::normalize(sc_World_Front_Dir);
	sc_World_Right_Dir = modelMatrix * glm::vec4(sc_local_right, 1.0f);
		sc_World_Right_Dir = glm::normalize(sc_World_Right_Dir);
	
	
	std::cout << "Spacecraft world pos: " << scTranslation.x <<  "," << scTranslation.z << "\n";

	object->draw(modelMatrix, view, proj, shader);


}

void Camera::ProcessMouseMovementNew(int x, int y) {


	if (x < oldx)
	{
		viewRotateDegree += 1.0f;
		sc_Rot_M = sc_Rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(viewRotateDegree), glm::vec3(0.0f, 1.0f, 0.0f));

	}
	if (x > oldx)
	{
		viewRotateDegree -= 1.0f;
		sc_Rot_M = sc_Rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(viewRotateDegree), glm::vec3(0.0f, 1.0f, 0.0f));

	}
	oldx = x;

	std::cout << x << "\n";

}


void Camera::UpdateNew() {

}
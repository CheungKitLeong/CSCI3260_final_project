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
	Position.x = speed * xPress;
	Position.z = speed * zPress;

	//Camera::ProcessMouseMovement(rotation);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)); //* cos(glm::radians(pitch));
	direction.y = 0.0f; //sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)); //* cos(glm::radians(pitch));
	Orientation = glm::normalize(direction);


}



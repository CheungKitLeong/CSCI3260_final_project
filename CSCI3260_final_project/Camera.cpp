#include "Camera.h"
#include "Model.h"
#include "Shader.h"

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"
#include "Dependencies/glm/gtx/vector_angle.hpp"

void Camera::update(Keys keyFlag, Mouse mouse) {
	glm::vec3 right = glm::normalize(glm::cross(orientation, up));
	up = glm::normalize(glm::cross(right, orientation));

	if (keyFlag.up) {
		position += speed * orientation;
	}
	if (keyFlag.down) {
		position -= speed * orientation;
	}
	if (keyFlag.left) {
		position -= speed * right;
	}
	if (keyFlag.right) {
		position += speed * right;
	}

	if (mouse.left) { // More natral move
		//float rotX = speed * (mouse.yClick - mouse.y);
		float rotY = sensitivity * (mouse.x - mouse.xClick);
		// Rotates the Orientation left and right
		orientation = glm::normalize(glm::rotate(orientation, glm::radians(-rotY), up));
		//std::cout << glm::angle(glm::vec3(0.0f,0.0f,-1.0f), orientation) << ";\n"; // << pitch << "\n";
	}

}


void Camera::set_flag(int key, int pressedKey, int action, bool& flag) {
	if (key == pressedKey && action == GLFW_PRESS) flag = true;
	if (key == pressedKey && action == GLFW_RELEASE) flag = false;
}

void Camera::draw_spacecraft(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader) {

	glm::vec3 planeOffSet = glm::vec3(0.0f, -0.3f, 0.0f);
	modelTrans = glm::mat4(1.0f);
	modelTrans = glm::translate(modelTrans, position + orientation + planeOffSet);
	modelTrans = glm::rotate(modelTrans, glm::orientedAngle(glm::vec3(0.0f, 0.0f, -1.0f), orientation, up), up);
	modelTrans = glm::scale(modelTrans, glm::vec3(0.0005, 0.0005, 0.0005));
	object->draw(modelTrans, view, proj, shader);

}


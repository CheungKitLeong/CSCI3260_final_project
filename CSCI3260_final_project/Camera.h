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


struct Keys { // For key holding events
	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	bool g = false;
};

struct Mouse { // For mouse capture
	double x = 800 / 2;
	double y = 600 / 2;
	bool left = false;
	bool right = false;
	double xClick = 800 / 2;
	double yClick = 600 / 2;
};


class Camera
{
public:

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float speed = 0.2f;
	float sensitivity = 0.01f;

	void static set_flag(int key, int pressedKey, int action, bool& flag);

	void update(Keys keyFlag, Mouse mouse);

	void draw_spacecraft(Model* object, glm::mat4 modelTrans, glm::mat4 view, glm::mat4 proj, Shader shader);

};

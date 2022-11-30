#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"

//#include "Model.h"
#include "Texture.h"
#include "Shader.h"



class SkyboxTexture : public Texture {
public:
	void setupSkyboxTexture();
	void bindCube();

};

class Skybox{
public:
	void setup();
	void drawSkybox(glm::mat4 view, glm::mat4 proj);

private:
	Shader skyboxShader;
	SkyboxTexture skyboxTexture;
	GLuint vaoID;
};


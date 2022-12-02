#pragma once

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"

#include "Shader.h"
#include "Texture.h"

#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>

struct LightParam {
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
};

class Model 
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Texture texture;
	Texture normal_texture;
	LightParam light_params;

	//bool use_strip;

	Model(const char* path);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj, Shader shader);

	void setTexture(const char* path);
	void setNormalTexture(const char* path);

protected:
	void constructVAO(bool skybox = false);
	GLuint vaoID;

private:
	bool normal_map;

	// load model from path
	void loadOBJ(const char* objPath);
	// make VAO, VBO and EBO


	void setPtLight(Shader shader, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	void setSpotLight(Shader shader, glm::vec3 color);

};
#include "Skybox.h"

#include "Dependencies/stb_image/stb_image.h"

#include <vector>

GLfloat skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

std::vector<const GLchar*> earth_faces
{
	"resources/skybox/right.bmp",
	"resources/skybox/left.bmp",
	"resources/skybox/bottom.bmp",
	"resources/skybox/top.bmp",
	"resources/skybox/front.bmp",
	"resources/skybox/back.bmp",
};

void Skybox::setup(){
	//for (int i = 0; i < 8; i++) {
	//	glm::vec3 p = glm::vec3(skyboxVertices[i * 3], skyboxVertices[i * 3 + 1], skyboxVertices[i * 3 + 2]);
	//	Vertex v = {};
	//	v.position = p;
	//	v.normal = glm::vec3(0.0f);
	//	v.uv = glm::vec2(0.0f);
	//	vertices.push_back(v);
	//}
	//indices = skyboxIndices;
	//constructVAO();
	//light_params.ambient = 0.1f;
	//light_params.diffuse = 0.6f;
	//light_params.specular = 0.3f;
	//light_params.shininess = 10.0f;
	GLuint vboID;

	// Generate things
	//glGenVertexArrays(1, &vaoID[id]);
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	//glGenBuffers(1, &eboID);

	// Binding vao vbo
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Store data in to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	//Binding ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), &(skyboxIndices[0]), GL_STATIC_DRAW);

	// model position
	glEnableVertexAttribArray(0);	//Enable the vertex attribute to use it later
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	skyboxShader.setupShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	skyboxShader.use();
	skyboxTexture.setupSkyboxTexture();
}

void Skybox::drawSkybox(glm::mat4 view, glm::mat4 proj) {
	glDepthFunc(GL_LEQUAL);
	skyboxShader.use();
	//skyboxShader.setMat4("model", model);
	glm::mat4 view_no_translate = glm::mat4(glm::mat3(view));
	skyboxShader.setMat4("view", view_no_translate);
	skyboxShader.setMat4("proj", proj);

	skyboxShader.setInt("skybox", 0);

	glBindVertexArray(vaoID);
	skyboxTexture.bindCube();

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void SkyboxTexture::setupSkyboxTexture() {
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	unsigned char* data;
	for (GLuint i = 0; i < earth_faces.size(); i++) {
		data = stbi_load(earth_faces[i], &Width, &Height, &BPP, 0);
		if (data) {
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else
		{
			std::cout << "Failed to load texture: " << earth_faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	std::cout << "Load skymap successfully!" << std::endl;
	glBindTexture(GL_TEXTURE_2D, 0);
	//stbi_image_free(data);
}

void SkyboxTexture::bindCube() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}


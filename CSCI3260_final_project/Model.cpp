#include "Model.h"

#include <map>
#include <iostream>
#include <fstream>
#include <string>

void Model::setPtLight(Shader shader, glm::vec3 color) {
	shader.setFloat("ptLight.constant", 1.0f);
	shader.setFloat("ptLight.linear", 0.09f);
	shader.setFloat("ptLight.quadratic", 0.032f);
	shader.setFloat("ptLight.intensity", 150.0f);

	shader.setVec3("ptLight.ambient", color * light_params.ambient);
	shader.setVec3("ptLight.diffuse", color * light_params.diffuse);
	shader.setVec3("ptLight.specular", color * light_params.specular);

	shader.setFloat("shininess", light_params.shininess);
}

void Model::setSpotLight(Shader shader, glm::vec3 color) {
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(5.0f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(7.5f)));

	shader.setVec3("spotLight.ambient", color * light_params.ambient);
	shader.setVec3("spotLight.diffuse", color * light_params.diffuse);
	shader.setVec3("spotLight.specular", color * light_params.specular);

	shader.setFloat("shininess", light_params.shininess);
}

Model::Model(const char* path){
	loadOBJ(path);
	constructVAO();
	light_params.ambient = 0.1f;
	light_params.diffuse = 0.6f;
	light_params.specular = 0.3f;
	light_params.shininess = 10.0f;
	normal_map = false;
	//use_strip = false;
}


void Model::setNormalTexture(const char* path) {
	normal_texture.setupTexture(path);
	normal_map = true;
}

void Model::setTexture(const char* path) {
	texture.setupTexture(path);
}

void Model::draw(glm::mat4 model, glm::mat4 view, glm::mat4 proj, Shader shader) {
	shader.use();
	setPtLight(shader);
	setSpotLight(shader, glm::vec3(0.8f, 0.0f, 0.0f));
	// Make uniform variables
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("proj", proj);

	shader.setInt("textSamp", 0);
	texture.bind(0);

	if (normal_map) {
		shader.setInt("normalMap", 1);

		shader.setInt("normalSamp", 1);
		normal_texture.bind(1);
	}
	else {
		shader.setInt("normalMap", 0);
	}

	glBindVertexArray(vaoID); // Bind VAO

	glDrawElements(GL_TRIANGLES, static_cast<unsigned int> (indices.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Model::loadOBJ(const char* objPath)
{
	// function to load the obj file
	// Note: this simple function cannot load all obj files.

	struct V {
		// struct for identify if a vertex has showed up
		unsigned int index_position, index_uv, index_normal;
		bool operator == (const V& v) const {
			return index_position == v.index_position && index_uv == v.index_uv && index_normal == v.index_normal;
		}
		bool operator < (const V& v) const {
			return (index_position < v.index_position) ||
				(index_position == v.index_position && index_uv < v.index_uv) ||
				(index_position == v.index_position && index_uv == v.index_uv && index_normal < v.index_normal);
		}
	};

	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::map<V, unsigned int> temp_vertices;

	// model;
	unsigned int num_vertices = 0;

	std::cout << "\nLoading OBJ file " << objPath << "..." << std::endl;

	std::ifstream file;
	file.open(objPath);

	// Check for Error
	if (file.fail()) {
		std::cerr << "Impossible to open the file! Do you use the right path? See Tutorial 6 for details" << std::endl;
		exit(1);
	}

	while (!file.eof()) {
		// process the object file
		char lineHeader[128];
		file >> lineHeader;

		if (strcmp(lineHeader, "v") == 0) {
			// geometric vertices
			glm::vec3 position;
			file >> position.x >> position.y >> position.z;
			temp_positions.push_back(position);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			// texture coordinates
			glm::vec2 uv;
			file >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			// vertex normals
			glm::vec3 normal;
			file >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			// Face elements
			V vs[3];
			for (int i = 0; i < 3; i++) {
				char ch;
				file >> vs[i].index_position >> ch >> vs[i].index_uv >> ch >> vs[i].index_normal;
			}

			// Check if there are more than three vertices in one face.
			std::string redundency;
			std::getline(file, redundency);
			if (redundency.length() >= 5) {
				std::cerr << "There may exist some errors while load the obj file. Error content: [" << redundency << " ]" << std::endl;
				std::cerr << "Please note that we only support the faces drawing with triangles. There are more than three vertices in one face." << std::endl;
				std::cerr << "Your obj file can't be read properly by our simple parser :-( Try exporting with other options." << std::endl;
				exit(1);
			}

			for (int i = 0; i < 3; i++) {
				if (temp_vertices.find(vs[i]) == temp_vertices.end()) {
					// the vertex never shows before
					Vertex vertex;
					vertex.position = temp_positions[vs[i].index_position - 1];
					vertex.uv = temp_uvs[vs[i].index_uv - 1];
					vertex.normal = temp_normals[vs[i].index_normal - 1];

					vertices.push_back(vertex);
					indices.push_back(num_vertices);
					temp_vertices[vs[i]] = num_vertices;
					num_vertices += 1;
				}
				else {
					// reuse the existing vertex
					unsigned int index = temp_vertices[vs[i]];
					indices.push_back(index);
				}
			} // for
		} // else if
		else {
			// it's not a vertex, texture coordinate, normal or face
			char stupidBuffer[1024];
			file.getline(stupidBuffer, 1024);
		}
	}
	file.close();

	std::cout << "There are " << num_vertices << " vertices in the obj file.\n" << std::endl;
	//return model;
}

void Model::constructVAO(bool skybox) {
	GLuint vboID, eboID;

	// Save indices size (don't need)
	//indices_count[id] = static_cast<unsigned int>(obj->indices.size());

	// Generate things
	//glGenVertexArrays(1, &vaoID[id]);
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &eboID);

	// Binding vao vbo
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Store data in to vbo
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

	//Binding ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &(indices[0]), GL_STATIC_DRAW);

	// model position
	glEnableVertexAttribArray(0);	//Enable the vertex attribute to use it later
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	if (!skybox) {
		// model uv
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

		// model normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	}

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
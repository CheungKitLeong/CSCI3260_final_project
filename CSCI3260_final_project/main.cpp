/*
Student Information
Student ID:
Student Name:
*/

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "AstrRing.h"
#include "Skybox.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>




// screen setting
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// global var
#define ORIGIN glm::vec3(0.0f)
Shader shader;
#define NUM_OBJ 4
Model* models[NUM_OBJ];
glm::vec3 sunPos = glm::vec3(-20.0f, -1.0f, -40.0f);

Camera camera;

//Create Astroid Ring, Set rock count and radius
AstrRing astrRing(200, 5);

Skybox skybox;


void cleanup() {
	for (int i = 0; i < NUM_OBJ; i++) {
		delete models[i];
	}
}

void get_OpenGL_info()
{
	// OpenGL information
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* glversion = glGetString(GL_VERSION);
	std::cout << "OpenGL company: " << name << std::endl;
	std::cout << "Renderer name: " << renderer << std::endl;
	std::cout << "OpenGL version: " << glversion << std::endl;
}

void sendDataToOpenGL()
{
	//TODO
	//Load objects and bind to VAO and VBO
	Model* planet = new Model("resources/object/planet.obj");
	planet->setTexture("resources/texture/earthTexture.bmp");
	planet->setNormalTexture("resources/texture/earthNormal.bmp");
	models[0] = planet;
	Model* spacecraft = new Model("resources/object/spacecraft.obj");
	spacecraft->setTexture("resources/texture/spacecraftTexture.bmp");
	models[1] = spacecraft;
	Model* rock = new Model("resources/object/rock.obj");
	rock->setTexture("resources/texture/rockTexture.bmp");
	models[2] = rock;

	//Load textures
}

void initializedGL(void) //run only once
{
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW not OK." << std::endl;
	}

	get_OpenGL_info();
	sendDataToOpenGL();

	//TODO: set up the camera parameters (Done in global var)	
	//TODO: set up the vertex shader and fragment shader
	shader.setupShader("VertexShaderCode.glsl", "FragmentShaderCode.glsl");

	//TODO: set up skybox
	skybox.setup();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void paintGL(void)  //run every frame
{
	glClearColor(0.35f, 0.65f, 0.65f, 1.0f); //specify the background color, this is just an example
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//TODO:
	//Set lighting information, such as position and color of lighting source
	shader.use();
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("ptLight.position", sunPos);
	// 
	//Set transformation matrix

	 
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(camera.Position , camera.Position + camera.Orientation, camera.Up);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
	
	
		// *** Drawing object 0: The planet
	glm::mat4 planetTrans = glm::translate(model, glm::vec3(0.0f, 0.0f, -50.0f));
	models[0]->draw(planetTrans, view, proj, shader);

		// *** Drawing object 1: the spacecraft
	camera.Object(models[1], model, view, proj, shader);


	/*
	glm::vec3 planeOffSet = glm::vec3(0.0f, -0.3f, 0.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, camera.Position + camera.Orientation + planeOffSet);
	//TO DO: Rotate spacecraft along with camera
	model = glm::scale(model, glm::vec3(0.0005, 0.0005, 0.0005));
	models[1]->draw(model, view, proj, shader);
	*/
	
		// *** Drawing object 2: The rock (1 only)
	astrRing.Render(models[2], planetTrans, view, proj, shader);

	camera.Update();

// *** Drawing skybox
	skybox.drawSkybox(view, proj);



	//Bind different textures
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

struct MouseController {
	bool LEFT_BUTTON = false;
	//double MOUSE_X = 0.0, MOUSE_Y = 0.0;
};

MouseController mouseCtl;


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mouseCtl.LEFT_BUTTON = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	};
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseCtl.LEFT_BUTTON = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.mouseNotMoving = true;
	};
	// Sets the mouse-button callback for the current window.	
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	if (mouseCtl.LEFT_BUTTON) {

		camera.ProcessMouseMovement(x);
	};
	// Sets the cursor position callback for the current window
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Sets the scoll callback for the current window.
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Sets the Keyboard callback for the current window.
		// *** 1. Transform the spacecraft with 4 directions
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		camera.xPress -= 1;
		std::cout << camera.xPress << " , " << camera.Position.x << "/";
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		camera.xPress += 1;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		camera.zPress -= 1;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		camera.zPress += 1;
	}

	// *** 2. Camera Rotation, for debug
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		camera.yaw -= 1;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		camera.yaw += 1;
	}
	

}


int main(int argc, char* argv[])
{

	GLFWwindow* window;

	/* Initialize the glfw */
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	/* glfw: configure; necessary for MAC */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 2", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/*register callback functions*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);                                                                  //    
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//camera.Inputs(window);

	initializedGL();

	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		paintGL();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	// free memory
	cleanup();

	return 0;
}







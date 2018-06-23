// Allow vec3(1,2,3).xz
//#define GLM_SWIZZLE

//Includes necessaires
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <time.h>

//Glew
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//.h
#include "Cube.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Terrain.h"
#include "Skybox.h"

using namespace glm;

#define WIDTH 1920 
#define HEIGHT 1080

extern float OMGL_RED[]		  = { 1.0f, 0.1f, 0.1f };
extern float OMGL_GREEN[]	  = { 0.1f, 1.0f, 0.1f };
extern float OMGL_BLUE[]	  = { 0.1f, 0.1f, 1.0f };
extern float OMGL_CYAN[]      = { 0.1f, 1.0f, 1.0f };
extern float OMGL_MAGENTA[]   = { 1.0f, 0.1f, 1.0f };
extern float OMGL_YELLOW[]    = { 1.0f, 1.0f, 0.1f };
extern float OMGL_BROWN[]     = { 0.34f, 0.16f, 0.0f };
extern float OMGL_GREY[]      = { 0.5f, 0.5f, 0.5f };
extern float OMGL_ORANGE[]    = { 1.0f, 0.27f, 0.0f };

int init();
int main(void);
GLFWwindow* window;

int init() {

	srand((unsigned int)time(0));

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a wubdower mode window and its OpenGL context 
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	// Needed by some drivers/hardware
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		return -1;
	//std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	// Enable depth test
	GLCall(glEnable(GL_DEPTH_TEST));
	// Accept fragment if it closer to the camera than the former one
	GLCall(glDepthFunc(GL_LESS));
}

int main(void) {

	init();
	Renderer renderer(*window, WIDTH, HEIGHT);

	glm::vec3 pos = renderer.getCameraPosition();

	glm::i32vec2 p;
  
	Terrain t(glm::vec2(pos.x, pos.z));

	Skybox s;



	//Cube cube;
	//Object c(&cube, OMGL_CYAN);
	//c.GenerateShaders("shaders/DynamicShader", "shaders/DynamicShader/Basic.genshader");
	//Object c(&cube, "shaders/Test.shader");

	//c.GenerateShaders("shaders/DynamicShader", "shaders/DynamicShader/Basic.genshader");
	//Object o("res/objects/bugatti/bugatti2.obj", "res/objects/bugatti/bugatti.mtl", false);
	//Object o("res/objects/dodge/CHALLENGER71.obj", "res/objects/dodge/CHALLENGER71.mtl", "res/objects/dodge/", true, GL_TRIANGLES);
	//Object o("res/objects/falcon/falcon.obj", "res/objects/falcon/falcon.mtl", "res/objects/falcon/", false, GL_TRIANGLES);

	//Object o("res/objects/Mill/Mill.obj", OMGL_CYAN, false);
	//Object o("res/objects/Mill/Mill.obj", "res/objects/Mill/Mill.mtl", false);

	//o.GenerateShaders("shaders/DynamicShader", "shaders/DynamicShader/Basic.genshader");

	//o.SetTextureDirectory("res/objects/dodge/");
	//o.LoadTexturesMap();
	//o.LoadTexturesMap("res/objects/dodge/");

	//o.RotationRad(3.1415/2, 0.0f, 1.0f, 0.0f);


	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		renderer.Clear();

		renderer.Clear();
		renderer.UpdateCamera();

		pos = renderer.getCameraPosition();
		p = glm::i32vec2(pos.x,pos.z);
		//printf("x:%f y:%f \n",pos.x,pos.z);    

	    t.Update(p);
		renderer.Draw(t);


		/*renderer.Draw(o);
		o.RotationDeg(vec3(0.0f, 0.3f, 0.0f));*/


		// Always draw last	
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderer.Draw(s);

		/* Swap frint and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process envents */
		glfwPollEvents();

	}
	//glDeleteTextures(1,c.GetTexture()->m_RendererID);
	glfwTerminate();
	return 0;
}


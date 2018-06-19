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

int init();
GLFWwindow* window;

int init(){

  srand((unsigned int)time(0));

  if(!glfwInit())
    return -1;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a wubdower mode window and its OpenGL context 
  window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
  if(!window){
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

int main(void){

  init();
  Renderer renderer(*window, WIDTH, HEIGHT);

  glm::vec3 pos = renderer.getCameraPosition();
  glm::i32vec2 p;
  
  Terrain t(glm::vec2(pos.x, pos.z));

  /*Skybox s("shaders/Skybox.shader", {
        "textures/grass.dds",
        "textures/grass.dds",
        "textures/grass.dds",
        "textures/grass.dds",
        "textures/grass.dds",
        "textures/grass.dds"
        });*/
  Skybox s;
  
  Cube cube;
  Object c(&cube, new Material((Texture*)t.m_HeightMap, new Shader("shaders/Cube.shader")));
  //Object c(&cube, new Material(new Texture("textures/grass.dds"), new Shader("shaders/Cube.shader")));
  //Object c(&cube, new Material("textures/grass.dds", "shaders/Object.shader"));
  //c.Translate(0,0,0);  // thats a f* problem right here
  //c.Translate(2,-10,0);
  //c.Init();
  c.Scale(1.0f,1.0f,1.0f);
  //c1.Scale(1,0.1,1);
  
  //Object o("res/objects/dodge/CHALLENGER71.obj", "res/objects/dodge/CHALLENGER71.mtl", true);
  //Object o("objects/Mill/Mill.obj", "objects/Mill/Mill.mtl", false);
  //o.Init(GL_TRIANGLES, "shaders/Object.shader");
  glm::vec3 a(20.0f,1.0f,20.0f);
  c.SetScale(a);

  // 
  // o.RotationDeg(90,0,0);
  // o.Translate(20,0,0);


  bool update = true;
  glm::vec2 pp(0);

  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
  {

    renderer.Clear();
    renderer.UpdateCamera();
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
      update = true;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
      update = false;
    }
    if(update){
      if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) {
        pp.x+=0.2f;
      }
      if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) {
        pp.x-=0.2f;
      }
      if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS) {
        pp.y-=0.2f;
      }
      if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) {
        pp.y+=0.2f;
      }
    }

    
    pos = renderer.getCameraPosition();
    p = glm::i32vec2(pp.x,pp.y);
    //printf("x:%f y:%f \n",pos.x,pos.z);    

    //renderer.Draw(c);
    if(update)
      t.Update(p);
    renderer.Draw(t);
  //  renderer.Draw(c1);
	//renderer.Draw(o);
	//o.RotationDeg(0.5, vec3(1.0f, 0.0f, 0.0f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Always draw last	
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


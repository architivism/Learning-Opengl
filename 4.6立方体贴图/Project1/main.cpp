
#define GLFW_STATIC
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
float vertices[]
{
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 0.0f

};
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(1.0f,  1.0f, 1.5f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -1.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -6.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
 
};
float grass_vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f
};
vector<glm::vec3> windows
{
	glm::vec3(-1.5f, 0.0f, -0.48f),
	glm::vec3(1.5f, 0.0f, 0.51f),
	glm::vec3(3.0f, 0.0f, -3.0f),
	glm::vec3(-0.3f, 0.0f, -2.3f),
	glm::vec3(0.5f, 0.0f, -0.6f)
};
float quadVertices[] = {
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};
float skyboxVertices[] = {
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
float skyBoxReflectionVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int Load_pic_to_GPU(const char* filename, GLint internalFormat, GLenum Format, int slot);
unsigned int loadCubeMap(vector<std::string>faces);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;
unsigned int flag = 0;

float lastX=400, lastY=300;
float fov = 45.0f;
float delatTime=0.0f, lastFrame=0.0f;
bool firstMouse = true;
Camera camera(glm::vec3(0, 0, 4.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));
int main(int argc, char* argv[])
{	
	
	std::string exePath = argv[0];
	cout << exePath << endl;
	glfwInit();	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail" << std::endl;
		return -1;
	}
	//glViewport(0,0,600,400);
	

	Shader testshader=Shader("vertexSource.vert","fragmentSource.frag");
	Shader lampshader =Shader("vertexSource.vert","fragmentSource1.frag");
	Shader grassshader = Shader("vertexSource.vert", "fragmentSource_grass.frag");
	Shader screenshader = Shader("vertex_Screen.vert","fragment_Screen.frag");
	Shader skyboxshader = Shader("skybox.vert","skybox.frag");
	Shader skyboxreflect = Shader("skybox_Reflect.vert","skybox_Reflect.frag");
	Material material = Material(testshader,
		glm::vec3(0.5f, 0.5f, 0.5f),
		Load_pic_to_GPU("container2.png",GL_RGBA,GL_RGBA,0),
		Load_pic_to_GPU("container2_specular.png", GL_RGBA, GL_RGBA,1),
		64.0f);
	Material material_grass = Material(grassshader,
		glm::vec3(0.5f, 0.5f, 0.5f),
		Load_pic_to_GPU("red_glass.png", GL_RGBA, GL_RGBA, 2),
		Load_pic_to_GPU("red_glass.png", GL_RGBA, GL_RGBA, 3),
		64.0f);
	LightDirectional lightD = LightDirectional(testshader,
		glm::vec3(1.0f, 1.0f, 2.0f),
		glm::vec3(0.1f, 0.1f, 0.1f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f));
	LightPoint lightP0 =LightPoint (testshader,
		glm::vec3(-10.0,0.0f,0.0f),
		glm::vec3(0.05f,0.05f,0.05f),
		glm::vec3(15.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,0.0f),1.0f,0.1f,0.1f);
	LightPoint lightP1 = LightPoint(testshader,
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.05f, 0.05f, 0.05f),
		glm::vec3(0.0f, 1.5f, 0.0f),
		glm::vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.1f, 0.032f);
	LightSpot lightS = LightSpot(testshader,
		camera.Position,
		camera.Forward,
		glm::vec3(0.5f,0.5f,0.0f),
		glm::vec3(1.0f,1.0f,1.0f),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::cos(glm::radians(4.0f)),
		glm::cos(glm::radians(6.0f)));

	vector<std::string> faces
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};
	unsigned int cubemapexture = loadCubeMap(faces);

 
#pragma region Init and Load Models to VAO,VBO
	Mesh cube(vertices);
	Mesh grass(grass_vertices);
	
	//Model model_in(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");

	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
#pragma endregion

#pragma region skybox_Reflect
	unsigned int skyBoxReflectionVAO, skyBoxReflectionVBO;
	glGenVertexArrays(1, &skyBoxReflectionVAO);
	glGenBuffers(1, &skyBoxReflectionVBO);
	glBindVertexArray(skyBoxReflectionVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxReflectionVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxReflectionVertices), &skyBoxReflectionVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region skyboxVAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1,&skyboxVAO);
	glBindVertexArray(skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER,skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
#pragma endregion

#pragma region fbo&rbo
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800.0f, 600.0f, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// renderbuffer object for depth and stencil
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	// use a single renderbuffer object for both a depth AND stencil buffer.
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800.0f, 600.0f);
	// now actually attach it
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	// check if complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	
#pragma endregion

	stbi_set_flip_vertically_on_load(true);
	while (!glfwWindowShouldClose(window))
	{
		 float currTime= glfwGetTime();
		 delatTime = currTime - lastFrame;
		 lastFrame = currTime;

		processInput(window);

		//第一阶段：渲染到自己建立的fbo
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glEnable(GL_DEPTH_TEST);
		

		//glEnable(GL_STENCIL_TEST);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);



		//Clear Screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	


	
		
		glm::mat4 model=glm::mat4(1.0f);
		glm::mat4 view= glm::mat4(1.0f);
		//view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
		view = camera.GetMatrixView();
		glm::mat4 projection= glm::mat4(1.0f);;
		projection = glm::perspective(glm::radians(fov), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);
		stbi_set_flip_vertically_on_load(true);

		//激活程序对象
	    testshader.use();

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_BUFFER, material.diffuse);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_BUFFER, material.specular);*/
		
		for (unsigned int i = 0; i < 10; i++)
		{
			if(i==10)
				model = glm::translate(glm::mat4(1.0f), { 0,-10,-5 });
			else
			model = glm::translate(model, cubePositions[i]);
			
			//float angle = 20.0f * i;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
			glUniform3f(glGetUniformLocation(testshader.ID, "material.ambient"), material.ambient.x,material.ambient.y,material.ambient.z);
			//glUniform3f(glGetUniformLocation(testshader.ID, "material.diffuse"), material.ambient.x, material.ambient.y, material.ambient.z);
			//glUniform1i(glGetUniformLocation(testshader.ID, "material.diffuse"), 0);
			//glUniform1i(glGetUniformLocation(testshader.ID, "material.specular"),1);
			//lightD
			glUniform3f(glGetUniformLocation(testshader.ID, "lightD.direction"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightD.ambient"), lightD.ambient.x, lightD.ambient.y, lightD.ambient.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightD.diffuse"), lightD.diffuse.x, lightD.diffuse.y, lightD.diffuse.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightD.specular"), lightD.specular.x, lightD.specular.y, lightD.specular.z);
			//lightp0
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP0.position"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP0.ambient"), lightP0.ambient.x, lightP0.ambient.y, lightP0.ambient.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP0.diffuse"), lightP0.diffuse.x, lightP0.diffuse.y, lightP0.diffuse.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP0.specular"), lightP0.specular.x, lightP0.specular.y, lightP0.specular.z);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP0.quadratic"), lightP0.quadratic);
			//lightp1
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP1.position"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP1.ambient"), lightP1.ambient.x, lightP1.ambient.y, lightP1.ambient.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP1.diffuse"), lightP1.diffuse.x, lightP1.diffuse.y, lightP1.diffuse.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightP1.specular"), lightP1.specular.x, lightP1.specular.y, lightP1.specular.z);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightP1.quadratic"), lightP1.quadratic);
			//lights
			glUniform3f(glGetUniformLocation(testshader.ID, "lightS.position"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightS.direction"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightS.ambient"), lightS.ambient.x, lightS.ambient.y, lightS.ambient.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightS.diffuse"), lightS.diffuse.x, lightS.diffuse.y, lightS.diffuse.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "lightS.specular"), lightS.specular.x, lightS.specular.y, lightS.specular.z);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightS.innercutoff"), lightS.innercutoff);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightS.outercutoff"), lightS.outercutoff);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(testshader.ID, "lightS.quadratic"), lightS.quadratic);
			
			/*glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);*/
			
			//glStencilFunc(GL_ALWAYS, 1, 0xFF);
			//glStencilMask(0xFF);
			testshader.use();
			cube.DrawArray(testshader, material.diffuse, material.specular);
			

		}
		
		lampshader.use();
		glm::mat4 model1 = glm::mat4(1.0f);
		for (unsigned int i = 0; i < 10; i++)
		{
			model1 = glm::translate(model1, cubePositions[i]);
			glm::mat4 modelMat = glm::scale(model1,glm::vec3(1.2,1.2,1.2));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			//glStencilMask(0x00);
			//cube.DrawArray(testshader, 1,1);
			
		}
		
		//glStencilMask(0xFF);
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);

		skyboxreflect.use();
		glm::mat4 model_skybox = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 2.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(skyboxreflect.ID, "model"), 1, GL_FALSE, glm::value_ptr(model_skybox));
		glUniformMatrix4fv(glGetUniformLocation(skyboxreflect.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxreflect.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(glGetUniformLocation(skyboxreflect.ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glBindVertexArray(skyBoxReflectionVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制天空盒
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		skyboxshader.use();
		glm::mat4 skybox_view = glm::mat4(glm::mat3(camera.GetMatrixView()));
		glUniformMatrix4fv(glGetUniformLocation(grassshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(skybox_view));
		glUniformMatrix4fv(glGetUniformLocation(grassshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		grassshader.use();
		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < windows.size(); i++)
		{
			float distance = glm::length(camera.Position-windows[i]);
			sorted[distance]=windows[i];
		}
		for (std::map<float,glm::vec3>::reverse_iterator it=sorted.rbegin();it!=sorted.rend();++it)
		{
			glm::mat4 model_grass = glm::mat4(1.0f);
			model_grass = glm::translate(model_grass, it->second);
			glUniformMatrix4fv(glGetUniformLocation(grassshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model_grass));
			glUniformMatrix4fv(glGetUniformLocation(grassshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(grassshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			grass.DrawSliceArray(grassshader, material_grass.diffuse, material_grass.specular);
		}
		//glEnable(GL_CULL_FACE);
		

		//第二阶段：渲染到默认的帧缓冲，绘制四边形
		//glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		
		//线框模式
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenshader.use();
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glUniform1i(glGetUniformLocation(screenshader.ID, "ScreenTexture"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDeleteVertexArrays(1, &quadVAO);*/
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	
	return 0;

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	float cameraSpeed = 2.5 * delatTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Position -= cameraSpeed * camera.Forward;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Position += cameraSpeed * camera.Forward;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Position -= cameraSpeed * glm::normalize(glm::cross(camera.Worldup, camera.Forward));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Position += cameraSpeed * glm::normalize(glm::cross(camera.Worldup, camera.Forward));
	}
}
unsigned int Load_pic_to_GPU(const char *filename,GLint internalFormat,GLenum Format,int slot)
{
	unsigned int Texturebuffer;
	flag++;
	glGenTextures(1, &Texturebuffer);
	glActiveTexture(GL_TEXTURE+slot);
	glBindTexture(GL_TEXTURE_2D, Texturebuffer);
	int width, height, nrChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,0, internalFormat,width,height,0,Format,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
		cout << flag << "haha" << endl;
	}
	else
	{
		std::cout << "Fail to Load pic!" << endl;
		cout << flag;
	}
	
	stbi_image_free(data);
	return Texturebuffer;
}
unsigned int loadCubeMap(vector<std::string>faces)
{
	unsigned int TextureID;
	glGenTextures(1,&TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP,TextureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), & width, & height, & nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return TextureID;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	cout << xoffset<<endl;
	cout << yoffset;
    
	float sensitivity = 0.005f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera.ProcesMouseMoment(xoffset,yoffset);

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov <= 45.0f && fov>=1.0f)
		fov -= yoffset;
	else if (fov > 45.0f)
		fov = 45.0f;
	else if (fov < 1.0f)
		fov = 1.0f;
}


#define GLFW_STATIC
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//float vertices[]
//{
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,     // 右上
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,      // 右下
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,      // 左下
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,      // 左上
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,      // 右上
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f      // 左下
//	
//};
float vertices[]
{
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, 15.0f),
 
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int Load_pic_to_GPU(const char* filename, GLint internalFormat, GLenum Format, int slot);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;
unsigned int flag = 0;

float lastX=400, lastY=300;
float fov = 45.0f;
float delatTime=0.0f, lastFrame=0.0f;
bool firstMouse = true;
Camera camera(glm::vec3(0, 0, 4.0f), 0.0f, 0.0f, glm::vec3(0, 1.0f, 0));
int main()
{	glfwInit();	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
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
	Material material = Material(testshader,
		glm::vec3(0.5f, 0.5f, 0.5f),
		Load_pic_to_GPU("container2.png",GL_RGBA,GL_RGBA,0),
		Load_pic_to_GPU("matrix.jpg", GL_RGB, GL_RGB,1),
		64.0f);
	Light light =Light (testshader,
		glm::vec3(cubePositions[1].x, cubePositions[1].y, cubePositions[1].z),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f));
    //Camera camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));
	
	
	//定义VAO与VBO
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//将顶点数据传入VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1,&lightVAO);
	glBindVertexArray(lightVAO);
		;
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	//将顶点数据传入VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//链接顶点属性
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	while (!glfwWindowShouldClose(window))
	{
		 float currTime= glfwGetTime();
		 delatTime = currTime - lastFrame;
		 lastFrame = currTime;

		processInput(window);
		
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glm::mat4 model=glm::mat4(1.0f);
		glm::mat4 view= glm::mat4(1.0f);
		//view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
		view = camera.GetMatrixView();
		glm::mat4 projection= glm::mat4(1.0f);;
		projection = glm::perspective(glm::radians(fov), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);

		//激活程序对象
	    testshader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_BUFFER, material.diffuse);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_BUFFER, material.specular);
		
		for (unsigned int i = 0; i < 1; i++)
		{
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(testshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
			glUniform3f(glGetUniformLocation(testshader.ID, "material.ambient"), material.ambient.x,material.ambient.y,material.ambient.z);
			/*glUniform3f(glGetUniformLocation(testshader.ID, "material.diffuse"), material.diffuse.x,material.diffuse.y,material.diffuse.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "material.specular"), material.specular.x, material.specular.y, material.specular.z);*/
			glUniform1i(glGetUniformLocation(testshader.ID, "material.diffuse"), 0);
			glUniform1i(glGetUniformLocation(testshader.ID, "material.specular"),1);

			
			glUniform3f(glGetUniformLocation(testshader.ID, "light.position"), light.Position.x, light.Position.y, light.Position.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "light.ambient"), light.ambient.x, light.ambient.y, light.ambient.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "light.diffuse"), light.diffuse.x, light.diffuse.y, light.diffuse.z);
			/*glUniform3f(glGetUniformLocation(testshader.ID, "light.ambient"), ambientColor.x, ambientColor.y, ambientColor.z);
			glUniform3f(glGetUniformLocation(testshader.ID, "light.diffuse"), diffuseColor.x, diffuseColor.y, diffuseColor.z);*/
			glUniform3f(glGetUniformLocation(testshader.ID, "light.specular"), light.specular.x, light.specular.y, light.specular.z);
			
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lampshader.use();

		for (unsigned int i = 1; i < 2; i++)
		{
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(lampshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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
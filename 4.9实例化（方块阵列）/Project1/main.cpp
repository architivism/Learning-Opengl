#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<iostream>
#include<string>
#include<sstream>

float vertices[]
{
	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
	 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

//Ӳ���붥����ɫ��
const char *vertexShaderSource="#version 330 core\n"
    "layout(location=0) in vec2 aPos;\n"
	"layout(location=1) in vec3 aColor;\n"
	"layout(location=2) in vec2 aOffset;\n"
	"out vec3 fColor;\n"
	"void main()\n"
	"{\n"
	"vec2 pos=aPos*(gl_InstanceID/100.0);\n"
	"  gl_Position=vec4(pos+aOffset,0.0,1.0);\n"
	"fColor=aColor;\n"
	"}\0";

//Ӳ����Ƭ����ɫ��
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 fColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(fColor,1.0f);\n"
"}\n\0"; 
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail" << std::endl;
		return -1;
	}
	//glViewport(0,0,600,400);
	
	//����VAO��VBO
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	//���������ݴ���VBO
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);




	//����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//����ɫ��Դ�븽������ɫ�������ϲ�����
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	//���Ҷ�����ɫ������
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//����ɫ��Դ�븽������ɫ�������ϲ�����
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	//����Ƭ����ɫ������
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//��֮ǰ�������ɫ�������ڳ��������
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	//�������Ӵ���
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//���Ӷ�������
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	glm::vec2 transforms[100];
	int index = 0;
	float offset = 0.1f;
	for (int i = -10; i < 10; i+=2)
	{
		for (int j = -10; j < 10; j+=2)
		{
			glm::vec2 transform;
			transform.y = (float)i/10.0+offset;
			transform.x = (float)j/10.0+offset;
			transforms[index++] = transform;
		}
	}

	//����instance
	unsigned int instanceVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER,instanceVBO);
	glBufferData(GL_ARRAY_BUFFER,  sizeof(glm::vec2) * 100,&transforms[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glVertexAttribDivisor(2,1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//����������
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES,0,3);
		glDrawArraysInstanced(GL_TRIANGLES,0,6,100);

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
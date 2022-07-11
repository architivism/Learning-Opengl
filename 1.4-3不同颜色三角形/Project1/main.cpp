#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

float vertices[]
{
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
};
float vertices1[]
{
	0.0f,0.5f,0.0f,
	0.5f,0.5f,0.0f,
	0.8f,0.3f,0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

//硬编码顶点着色器
const char *vertexShaderSource="#version 330 core\n"
    "layout(location=0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"  gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
	"}\0";

//硬编码片段着色器
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n\0";

//硬编码片段着色器
const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor=vec4(1.0f,1.0f,0.5f,1.0f);\n"
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
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//定义VAO与VBO与EBO
	unsigned int VAO[2];
	glGenVertexArrays(2,VAO);
	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glEnable(GL_CULL_FACE);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1),vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//将着色器源码附着在着色器对象上并编译
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	//查找顶点着色器错误
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//创建片段着色器
	unsigned int fragmentShader,fragmentShader1;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);

	//将着色器源码附着在着色器对象上并编译
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	glShaderSource(fragmentShader1,1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);

	//查找片段着色器错误
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//创建着色器程序
	unsigned int shaderProgramorange,shaderPorgramyellow;
	shaderProgramorange = glCreateProgram();
	shaderPorgramyellow = glCreateProgram();

	//将之前编译的着色器附着在程序对象上
	glAttachShader(shaderProgramorange,vertexShader);
	glAttachShader(shaderProgramorange,fragmentShader);
	glLinkProgram(shaderProgramorange);

	glAttachShader(shaderPorgramyellow, vertexShader);
	glAttachShader(shaderPorgramyellow, fragmentShader1);
	glLinkProgram(shaderPorgramyellow);

	//查找链接错误
	glGetShaderiv(shaderPorgramyellow, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderPorgramyellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//激活程序对象
		
		glUseProgram(shaderProgramorange);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES,0,3);
		
		glUseProgram(shaderPorgramyellow);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(2,VAO);
	glDeleteBuffers(2,VBO);
	glDeleteProgram(shaderProgramorange);
	glDeleteProgram(shaderPorgramyellow);

	
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
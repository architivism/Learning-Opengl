#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

float vertices[]
{
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // ����
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // ����
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // ����
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // ����
};
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

//Ӳ���붥����ɫ��
const char *vertexShaderSource="#version 330 core\n"
    "layout(location=0) in vec2 aPos;\n"
	"layout(location=1) in vec3 aColor;\n"
    "out VS_OUT{\n "
	"vec3 color;\n"
	"}vs_out;\n"
	"void main()\n"
	"{\n"
	"  gl_Position=vec4(aPos.x,aPos.y,0.0,1.0);\n"
	"vs_out.color=aColor;\n"
	"}\n";
//Ӳ���뼸����ɫ��
const char* geometryShaderSource = "#version 330 core\n"
"layout(points) in;\n"
"layout(triangle_strip,max_vertices=5)out;\n"

"in VS_OUT{\n"
"vec3 color;\n"
"}gs_in[];\n"

"out vec3 fColor;\n"

"void build_house(vec4 position){\n"
"fColor = gs_in[0].color;\n"
"gl_Position=position+vec4(-0.2,-0.2,0.0,0.0);\n"
"EmitVertex();\n"
"gl_Position=position+vec4(0.2,-0.2,0.0,0.0);\n"
"EmitVertex();\n"
"gl_Position=position+vec4(-0.2,0.2,0.0,0.0);\n"
"EmitVertex();\n"
"gl_Position=position+vec4(0.2,0.2,0.0,0.0);\n"
"fColor = vec3(1.0,1.0,1.0);\n"
"EmitVertex();\n"
"gl_Position=position+vec4(0.0,0.4,0.0,0.0);\n"
"fColor = vec3(1.0,1.0,1.0);\n"
"EmitVertex();\n"
"EndPrimitive();}\n"

"void main(){\n"
"build_house(gl_in[0].gl_Position);\n"
"}\n";
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

	//����������ɫ��
	unsigned int geometryShader;
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	//����ɫ��Դ�븽������ɫ�������ϲ�����
	glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
	glCompileShader(geometryShader);

	//����Ƭ����ɫ������
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//��֮ǰ�������ɫ�������ڳ��������
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
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
	glDeleteShader(geometryShader);

	//���Ӷ�������
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

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
		glDrawArrays(GL_POINTS,0,4);

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
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

#define GLFW_STATIC
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexsstream;
	stringstream fragmentsstream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit||ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit||ifstream::badbit);

	try
	{

		if (!vertexFile.is_open()||!fragmentFile.is_open())
			throw exception("open file  errer");
		vertexsstream << vertexFile.rdbuf();
		fragmentsstream << fragmentFile.rdbuf();

		vertexstring = vertexsstream.str();
		fragmentstring = fragmentsstream.str();

	}
	catch (const exception &ex)
	{
		printf(ex.what());
	
	}
	vertexSource = vertexstring.c_str();
	fragmentSource = fragmentstring.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompleErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompleErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompleErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompleErrors(unsigned int ID, string type)
{
	int success;
	char infoLog[512];

	if (type != "PROGRAM")
	{
		glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);
			cout << "shader compile error:" << infoLog << endl;
		}
	
	}
	else
	{
		glGetProgramiv(ID,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(ID,512,NULL,infoLog);
			cout << "program compile error:" << infoLog << endl;
		}
	
	}
}

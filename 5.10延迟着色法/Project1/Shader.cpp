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
	checkCompleErrors(vertex, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompleErrors(vertex, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	ifstream geometryFile;
	stringstream vertexsstream;
	stringstream fragmentsstream;
	stringstream geometrysstream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	geometryFile.open(geometryPath);

	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	geometryFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{

		if (!vertexFile.is_open() || !fragmentFile.is_open() || !geometryFile.is_open())
			throw exception("open file  errer");
		vertexsstream << vertexFile.rdbuf();
		fragmentsstream << fragmentFile.rdbuf();
		geometrysstream << geometryFile.rdbuf();

		vertexstring = vertexsstream.str();
		fragmentstring = fragmentsstream.str();
		geometrystring = geometrysstream.str();

	}
	catch (const exception& ex)
	{
		printf(ex.what());

	}
	vertexSource = vertexstring.c_str();
	fragmentSource = fragmentstring.c_str();
	geometrySource = geometrystring.c_str();

	unsigned int vertex, fragment, geometry;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompleErrors(vertex, "VERTEX");

	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &geometrySource, NULL);
	glCompileShader(geometry);
	checkCompleErrors(geometry, "GEOMETRY");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompleErrors(fragment, "FRAGMENT");


	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompleErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(geometry);
	glDeleteShader(fragment);
}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char* paraNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paraNameString), param.x, param.y, param.z);
}

void Shader::SetUniform4M(const char* paraNameString, glm::mat4 param)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, paraNameString), 1, GL_FALSE, glm::value_ptr(param));
}

void Shader::SetUniform1f(const char* paraNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paraNameString), param);
}


void Shader::SetUniform1i(const char* paraNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paraNameString), slot);
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

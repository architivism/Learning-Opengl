#pragma once
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath,const char* geometryPath);
	string vertexstring;
	string fragmentstring;
	string geometrystring;
	const char* vertexSource = {};
	const char* fragmentSource = {};
	const char* geometrySource = {};
	unsigned int ID=0;
	enum slot
	{
		DIFFUSE,
		SPECULAR
	};
	void use();
	void SetUniform3f(const char* paraNameString, glm::vec3 param);
	void SetUniform4M(const char* paraNameString, glm::mat4 param);
	void SetUniform1f(const char* paraNameString, float param);
	void SetUniform1i(const char* paraNameString, int slot);
private:
	void checkCompleErrors(unsigned int ID, string type);
};


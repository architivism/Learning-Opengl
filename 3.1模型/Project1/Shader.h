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
	string vertexstring;
	string fragmentstring;
	const char* vertexSource = {};
	const char* fragmentSource = {};
	unsigned int ID=0;
	enum slot
	{
		DIFFUSE,
		SPECULAR
	};
	void use();
	void SetUniform3f(const char* paraNameString, glm::vec3 param);
	void SetUniform1f(const char* paraNameString, float param);
	void SetUniform1i(const char* paraNameString, int slot);
private:
	void checkCompleErrors(unsigned int ID, string type);
};


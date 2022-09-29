#pragma once
#include<string>

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
private:
	void checkCompleErrors(unsigned int ID, string type);
};


#pragma once
#include<string>

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
	void use();
	void setFloat(const string &name,float value);
	void setBool(const string& name, bool value);
	void setInt(const string& name, int value);
private:
	void checkCompleErrors(unsigned int ID, string type);
};


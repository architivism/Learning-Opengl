#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Material
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shineness;
	Material(Shader shader,glm::vec3 _ambient,glm::vec3 _diffuse,glm::vec3 _specular,float _shineness);
	
};


#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Material
{
public:
	glm::vec3 ambient;
	unsigned int diffuse;
	unsigned specular;
	float shineness;
	Material(Shader shader,glm::vec3 _ambient,unsigned int _diffuse,unsigned int _specular,float _shineness);
	
};


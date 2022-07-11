#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
class LightDirectional
{
public:
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	LightDirectional(Shader shader,glm::vec3 _direction,glm::vec3 _ambient,glm::vec3 _diffuse,glm::vec3 _specular);

};


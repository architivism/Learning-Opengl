#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
class LightSpot
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	float innercutoff;
	float outercutoff;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	LightSpot(Shader shader, glm::vec3 _position, glm::vec3 _direction,glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular,float _cutoff,float _outercutoff);

};


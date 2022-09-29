#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
class LightPoint
{
public:
	glm::vec3 position;
	glm::vec3 color;

	float constant;
	float linear;
	float quadratic;
	LightPoint(Shader shader, glm::vec3 _position, glm::vec3 color,float _constant,float _linear,float _quadratic);

};

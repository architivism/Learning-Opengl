#include "LightDirectional.h"

LightDirectional::LightDirectional(Shader shader, glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular):
	direction(_direction),ambient(_ambient),diffuse(_diffuse),specular(_specular)
{
}

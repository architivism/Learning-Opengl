#include "Light.h"

Light::Light(Shader shader, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular):
	Position(_position),ambient(_ambient),diffuse(_diffuse),specular(_specular)
{
}

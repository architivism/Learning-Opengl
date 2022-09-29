#include "LightSpot.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

LightSpot::LightSpot(Shader shader, glm::vec3 _position, glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _cutoff,float _outercutoff):
	position(_position),direction(_direction),ambient(_ambient),diffuse(_diffuse),specular(_specular),innercutoff(_cutoff),outercutoff(_outercutoff)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
}

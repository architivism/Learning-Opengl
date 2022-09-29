#include "Material.h"
#include "Shader.h"

Material::Material(Shader shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular,float _shineness):
	ambient(_ambient),diffuse(_diffuse),specular(_specular),shineness(_shineness)
{
}


#include "LightPoint.h"

LightPoint::LightPoint(Shader shader, glm::vec3 _position, glm::vec3 _color, float _constant, float _linear, float _quadratic):
position(_position),color(_color), constant(_constant), linear(_linear), quadratic(_quadratic)
{
}

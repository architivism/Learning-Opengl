#version 330 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNormals;

out vec3 Normals;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   Normals=mat3(transpose(inverse(model)))*aNormals;
   gl_Position=projection*view*model*vec4(aPos,1.0f);
   Position=vec3(model*vec4(aPos,1.0f));
}
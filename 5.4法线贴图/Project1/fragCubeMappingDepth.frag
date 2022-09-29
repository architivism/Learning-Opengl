#version 330 core
in vec4 FragPos;

uniform float far_plane;
uniform vec3 lightPos;

void main()
{
   float Distance=length(FragPos.xyz-lightPos);
   Distance=Distance/far_plane;
   gl_FragDepth=Distance;
}
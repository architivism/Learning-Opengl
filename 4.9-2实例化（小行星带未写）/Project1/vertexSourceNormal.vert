#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=3)in vec2 TexCoord;

out VS_OUT{
  vec3 Normal;
  }vs_out;

void main()
{
   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);
   vs_out.Normal=aNormal;
}
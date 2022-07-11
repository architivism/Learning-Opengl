#version 330 core
layout (triangles) in;
layout(triangle_strip,max_vertices=3)out;

in VS_OUT {
    vec2 texCoords;
    mat4 model1;
} gs_in[];

out vec2 TexCoord;
out vec3 FragPos;
uniform float time;

out vec3 Normal;
vec4 explodePosition;

layout(std140) uniform Matrices
	  {
	    mat4 projection;
	    mat4 view;
	    
	  };

vec4 explode(vec4 position,vec3 normal)
{
   float magnitude=1.0;
   vec3 direction=normal*((sin(time)+1.0)/2.0)*magnitude;
   return position+vec4(direction.xyz,0.0);
}

vec3 GetNormal()
{
   vec3 a=vec3(gl_in[0].gl_Position-gl_in[1].gl_Position);
   vec3 b=vec3(gl_in[2].gl_Position-gl_in[1].gl_Position);
   return normalize(cross(b,a));
}

void main()
{
  vec3 normal=GetNormal();
  mat3 normalMatrix = mat3(transpose(inverse(gs_in[0].model1)));
  Normal=normalMatrix*normal;

  explodePosition=gs_in[0].model1*explode(gl_in[0].gl_Position,normal);
  FragPos=explodePosition.xyz;
  gl_Position=projection*view*explodePosition;
  TexCoord=gs_in[0].texCoords;
  EmitVertex();

  explodePosition=gs_in[1].model1*explode(gl_in[1].gl_Position,normal);
  FragPos=explodePosition.xyz;
  gl_Position=projection*view*explodePosition;
  TexCoord=gs_in[1].texCoords;
  EmitVertex();

  explodePosition=gs_in[2].model1*explode(gl_in[2].gl_Position,normal);
  FragPos=explodePosition.xyz;
  gl_Position=projection*view*explodePosition;
  TexCoord=gs_in[2].texCoords;
  EmitVertex();

  EndPrimitive();
}
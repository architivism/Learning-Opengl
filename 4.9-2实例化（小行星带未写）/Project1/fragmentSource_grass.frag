 #version 330 core
out vec4 FragColor;
in vec2 TexCoord;

struct Material
{
  vec3 ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};
uniform sampler2D material_grass;
void main()
{
  vec4 texColor=texture(material_grass,TexCoord);
  
  FragColor=texColor;
}
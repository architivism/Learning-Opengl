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
uniform Material material_grass;

void main()
{
  FragColor = texture(material_grass.diffuse, TexCoord);
}
 #version 330 core
out vec4 FragColor;
in vec3 LightPos;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    float ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewpos;
void main()
{
  
  vec3 ambient  = light.ambient *vec3(texture( material.diffuse,TexCoord));
 
  vec3 norm=normalize(Normal);
  vec3 lightdir=normalize(light.position-FragPos);
  
  float diff=max(dot(norm,lightdir),0);
  vec3 diffuse  = light.diffuse * (diff *vec3(texture( material.diffuse,TexCoord)));

  vec3 reflectdir=reflect(-lightdir,norm);
  vec3 viewdir=normalize(viewpos-FragPos);
  float spec=pow(max(dot(reflectdir,viewdir),0),material.shininess);
  vec3 specular = light.specular * spec *(-vec3(texture( material.specular,TexCoord)));
   vec3 result=ambient+diffuse+specular;
  FragColor=vec4(result,1.0f);
}
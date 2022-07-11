 #version 330 core
out vec4 FragColor;
in vec3 LightPos;
in vec3 FragPos;
in vec3 Normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
  
  vec3 ambient  = light.ambient * material.ambient;
 
  vec3 norm=normalize(Normal);
  vec3 lightdir=normalize(FragPos-light.position);
  
  float diff=max(dot(norm,lightdir),0);
  vec3 diffuse  = light.diffuse * (diff * material.diffuse);

  vec3 reflectdir=reflect(lightdir,norm);
  vec3 viewdir=normalize(viewpos-FragPos);
  float spec=pow(max(dot(reflectdir,viewdir),0),32);
  vec3 specular = light.specular * (spec * material.specular);
   vec3 result=ambient+diffuse+specular;
  FragColor=vec4(result,1.0f);
}
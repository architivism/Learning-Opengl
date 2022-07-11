 #version 330 core
out vec4 FragColor;
in vec3 LightPos;
in vec3 FragPos;
in vec3 Normal;


uniform vec3 objcolor;
uniform vec3 ambientcolor;
uniform vec3 lightcolor;

uniform vec3 viewpos;
void main()
{
  
  float ambientStrength=0.1;
  vec3 ambient=ambientStrength*ambientcolor;
 

  vec3 norm=normalize(Normal);
  vec3 lightdir=normalize(FragPos-LightPos);
  
  float diff=max(dot(norm,lightdir),0);
  vec3 diffuse=diff*lightcolor;

  float specularstrength=0.5;
  vec3 reflectdir=reflect(lightdir,norm);
  vec3 viewdir=normalize(viewpos-FragPos);
  float spec=pow(max(dot(reflectdir,viewdir),0),32);
  vec3 specular=specularstrength*spec*lightcolor;
   vec3 result=(ambient+diffuse+specular)*objcolor;
  FragColor=vec4(result,1.0f);
}
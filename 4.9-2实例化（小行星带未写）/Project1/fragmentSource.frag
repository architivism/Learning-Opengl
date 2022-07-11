 #version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    float ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct LightD {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
struct LightP {
    
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
struct LightS {
    vec3 position;
    vec3 direction;
    float innercutoff;
    float outercutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform LightD lightD;
uniform LightP lightP0;
uniform LightP lightP1;
uniform LightS lightS;

uniform vec3 viewpos;

vec3 CalcDirLight(LightD light,vec3 normal,vec3 DirToCamera)
{
  //ambient
  vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoord));
  //diffuse
  vec3 dirtoLight=normalize(light.direction);
  float diff=max(dot(normal,dirtoLight),0);
  vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoord));

  //specular
  vec3 ref=reflect(-dirtoLight,normal);
  float spec=pow(max(0,dot(ref,DirToCamera)),material.shininess);
  vec3 specular=light.specular*spec*vec3(texture(material.specular,TexCoord));

  vec3 FinalResult=ambient+diffuse+specular;
  return FinalResult;
}

vec3 CalcPointLight(LightP light,vec3 normal,vec3 DirToCamera,vec3 fragpos)
{
  //attenuation
  float dist=length(light.position-fragpos);
  float attenuation=1.0f/(light.constant+light.linear*dist+light.quadratic*dist*dist);
  //ambient
  vec3 ambient=light.ambient *vec3(texture( material.diffuse,TexCoord));
  //diffuse
  vec3 dirtoLight=normalize(light.position-fragpos);
  float diff=max(dot(normal,dirtoLight),0);
  vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoord));

  //specular
  vec3 ref=reflect(-dirtoLight,normal);
  float spec=pow(max(0,dot(ref,DirToCamera)),material.shininess);
  vec3 specular=light.specular*spec*vec3(texture(material.specular,TexCoord));

  vec3 FinalResult=(ambient+diffuse+specular)*attenuation;
  return FinalResult;
}

vec3 CalcSpotLight(LightS light,vec3 normal,vec3 DirToCamera,vec3 fragpos)
{
  //attenuation
  float dist=length(light.position-fragpos);
  float attenuation=1.0f/(light.constant+light.linear*dist+light.quadratic*dist*dist);
  //ambient
  vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoord));
  //diffuse
  vec3 dirtoLight=normalize(light.position-fragpos);
  float diff=max(dot(normal,dirtoLight),0);
  vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoord));

  //specular
  vec3 ref=normalize(reflect(-dirtoLight,normal));
  float spec=pow(max(0,dot(ref,DirToCamera)),material.shininess);
  vec3 specular=light.specular*spec*vec3(texture(material.specular,TexCoord));

  //spotRadio
  float thea=dot(light.direction,dirtoLight);
  float spotRadio=(thea-light.outercutoff)/(light.innercutoff-light.outercutoff);

  vec3 FinalResult;
  if(thea>light.innercutoff)
  {
      FinalResult=(ambient+diffuse+specular)*attenuation;
  }
  else if(thea<light.innercutoff&&thea>light.outercutoff)
  {
      FinalResult=(ambient+diffuse+specular)*attenuation*spotRadio;
  }
  else 
      FinalResult=vec3(0);

  return FinalResult;
}
void main()
{
  vec3 norm=normalize(Normal);
  vec3 DirtoCamera=normalize(viewpos-FragPos);
  vec3 result;
  result=CalcDirLight(lightD,norm,DirtoCamera);
  result+=CalcPointLight(lightP0,norm,DirtoCamera,FragPos);
  result+=CalcPointLight(lightP1,norm,DirtoCamera,FragPos);
  //result+=CalcSpotLight(lightS,norm,DirtoCamera,FragPos);
  FragColor=vec4(result,1.0);
}
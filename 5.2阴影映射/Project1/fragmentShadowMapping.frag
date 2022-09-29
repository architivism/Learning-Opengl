#version 330 core

out vec4 FragColor;
in VS_OUT{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
  vec4 FragPosLightSpace;
}fs_out;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 viewPos;
uniform vec3 lightPos;

float ShadowCalculation(vec4 fragPosLightSpace,float bias)
{
   vec3 projCoord=fragPosLightSpace.xyz/fragPosLightSpace.w;
   projCoord=projCoord*0.5+0.5;
   //float closeDepth=texture(shadowMap,projCoord.xy).r;
   float currDepth=projCoord.z;
   float shadow=0.0;
   vec2 texSize=1.0/textureSize(shadowMap,0);
   for(int i=-1;i<=1;i++)
   {
   for(int j=-1;j<=1;j++)
   {
      float pcfDepth=texture(shadowMap,projCoord.xy+vec2(i,j)*texSize).r;
      shadow += ((currDepth - bias )> pcfDepth) ? 1.0 : 0.0;
   }
   }
   shadow/=9.0;
   if (projCoord.z>1.0)
   shadow=0.0;
   return shadow;
}

void main(){
    vec3 color=texture(diffuseTexture,fs_out.TexCoord).rgb;
    vec3 normal=normalize(fs_out.Normal);
    vec3 lightcolor=vec3(1.0);
    //ambient
    vec3 ambient=0.5*lightcolor;
    //diffuse
    vec3 lightdir=normalize(lightPos-fs_out.FragPos);
    float diff=max(dot(lightdir,normal),0);
    vec3 diffuse=diff*lightcolor;
    //specular
    vec3 viewdir=normalize(viewPos-fs_out.FragPos);
    vec3 reflectdir=reflect(-lightdir,normal);
    vec3 halfdir=normalize(lightdir+viewdir);
    float spec=pow(max(dot(normal,halfdir),0),64.0);
    vec3 specular=spec*lightcolor;
    float bias=max(0.05*(1-dot(normal,lightdir)),0.005);
    float shadow=ShadowCalculation(fs_out.FragPosLightSpace,bias);
    vec3 lighting=(ambient+(1-shadow)*(diffuse+specular))*color;
    FragColor=vec4(lighting,1.0f);
}
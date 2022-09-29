#version 330 core

out vec4 FragColor;
in VS_OUT{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoord;
}fs_out;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform  bool shadows;
uniform float far_plane;

float ShadowCalculation(vec3 fragPos,float bias)
{
   vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);
   int samples=20;
   float shadow=0.0;
   float viewDistance=length(viewPos-fs_out.FragPos);
   float diskRadius=(1.0+(viewDistance/far_plane))/25.0;
   vec3 fragTolight=fragPos-lightPos;
   for(int i=0;i<samples;i++)
   {
   float closestDepth=texture(depthMap,fragTolight+diskRadius*sampleOffsetDirections[i]).r;
   closestDepth*=far_plane;
   float currDepth=length(fragPos-lightPos);
   if(currDepth-bias>closestDepth)
   shadow+=1.0;
   }
   shadow/=float(samples);
   return shadow;
}

void main(){
    vec3 color=texture(diffuseTexture,fs_out.TexCoord).rgb;
    vec3 normal=normalize(fs_out.Normal);
    vec3 lightcolor=vec3(0.5);
    //ambient
    vec3 ambient=0.3*lightcolor;
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
    float bias=max(0.05*(1-dot(normal,lightdir)),0.05);
    float shadow = shadows ? ShadowCalculation(fs_out.FragPos,bias) : 0.0;
   // float shadow =  ShadowCalculation(fs_out.FragPos,bias); 
    vec3 lighting=(ambient+(1-shadow)*(diffuse+specular))*color;
    FragColor=vec4(lighting,1.0f);
}
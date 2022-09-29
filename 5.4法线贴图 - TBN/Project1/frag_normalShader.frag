#version 330 core
in VS_OUT{
 vec3 FragPos;
 vec2 TexCoords;
 vec3 TangentViewPos;
 vec3 TangentLightPos;
 vec3 TangentFragPos;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

struct LightPoint{
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

uniform LightPoint lightP0;

out vec4 FragColor;
uniform vec3 ambientColor;

vec3 CalLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
     vec3 dirTolight=normalize(fs_in.TangentLightPos-fs_in.TangentFragPos);
     //diffuse
     float diffIntensity=max(dot(dirTolight,uNormal),0.0);
     vec3 diffuseColor=diffIntensity*texture(diffuseTexture,fs_in.TexCoords).rgb*light.color;
     //speculair
     vec3 hairdir=normalize(dirTolight+dirToCamera);
     float specularAmount=pow(max(dot(uNormal,hairdir),0.0),64.0);
     vec3 specularColor=specularAmount*texture(diffuseTexture,fs_in.TexCoords).rgb*light.color;
     vec3 result=diffuseColor+specularColor;
     return result;
}
void main()
{
    vec3 uNormal=texture(normalTexture,fs_in.TexCoords).rgb;
    uNormal=normalize(uNormal*2.0-1.0);
    vec3 dirTocamera=normalize(fs_in.TangentViewPos-fs_in.TangentFragPos);
    vec3 finalResult=ambientColor+CalLightPoint(lightP0,uNormal,dirTocamera);
    FragColor=vec4(finalResult,1.0f);
}
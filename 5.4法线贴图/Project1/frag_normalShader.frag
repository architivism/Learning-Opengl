#version 330 core
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

struct LightPoint{
    vec3 pos;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

uniform LightPoint lightP0;

out vec4 FragColor;

uniform vec3 cameraPos;
uniform vec3 ambientColor;

vec3 CalLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera)
{
     vec3 dirTolight=normalize(light.pos-FragPos);
     //diffuse
     float diffIntensity=max(dot(dirTolight,uNormal),0.0);
     vec3 diffuseColor=diffIntensity*texture(diffuseTexture,TexCoord).rgb*light.color;
     //speculair
     vec3 hairdir=normalize(dirTolight=dirToCamera);
     float specularAmount=pow(max(dot(uNormal,hairdir),0.0),64.0);
     vec3 specularColor=specularAmount*texture(diffuseTexture,TexCoord).rgb*light.color;
     vec3 result=diffuseColor+specularColor;
     return result;
}
void main()
{
    vec3 uNormal=texture(normalTexture,TexCoord).rgb;
    uNormal=normalize(uNormal*2.0-1.0);
    vec3 dirTocamera=normalize(cameraPos-FragPos);
    vec3 finalResult=ambientColor+CalLightPoint(lightP0,uNormal,dirTocamera);
    FragColor=vec4(finalResult,1.0f);
}
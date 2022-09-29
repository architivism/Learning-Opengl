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
uniform sampler2D parallaxTexture;

struct LightPoint{
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

uniform LightPoint lightP0;
uniform float height_scale;
out vec4 FragColor;
uniform vec3 ambientColor;

vec3 CalLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera,vec2 TexCoords)
{
     vec3 dirTolight=normalize(fs_in.TangentLightPos-fs_in.TangentFragPos);
     //diffuse
     float diffIntensity=max(dot(dirTolight,uNormal),0.0);
     vec3 diffuseColor=diffIntensity*texture(diffuseTexture,TexCoords).rgb*light.color;
     //speculair
     vec3 hairdir=normalize(dirTolight+dirToCamera);
     float specularAmount=pow(max(dot(uNormal,hairdir),0.0),32.0);
     vec3 specularColor=specularAmount*texture(diffuseTexture,TexCoords).rgb*light.color;
     vec3 result=diffuseColor+specularColor;
     return result;
}
//普通视差贴图
//vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
//{ 
//    float height =  texture(parallaxTexture, texCoords).r;    
//    vec2 p = viewDir.xy  * height * height_scale;
//    //vec2 p = viewDir.xy/viewDir.z  * height * height_scale;
//    return texCoords - p;    
//}

//陡峭视差映射
//vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir)
//{
//    const float numberlayer=10.0;
//    float layerDepth=1.0/numberlayer;
//    vec2 p=viewDir.xy*height_scale;
//    vec2 deltaTexcoords=p/numberlayer;
//    float currLayerDepth=0.0;
//
//    vec2 currTexcoords=texCoords;
//    float currDepthMapValue=texture(parallaxTexture,texCoords).r;
//    while(currLayerDepth<currDepthMapValue)
//    {
//        currTexcoords-=deltaTexcoords;
//        currDepthMapValue=texture(parallaxTexture,currTexcoords).r;
//        currLayerDepth+=layerDepth;
//    }
//    return currTexcoords;
//}

//视差遮蔽映射
vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir)
{
    const float minlayer=8.0;
    const float maxlayer=32.0;
    float numberlayer=mix(maxlayer,minlayer,max(dot(vec3(0.0,0.0,1.0),viewDir),0.0));
    float layerDepth=1.0/numberlayer;
    vec2 p=viewDir.xy*height_scale;
    vec2 deltaTexcoords=p/numberlayer;
    float currLayerDepth=0.0;

    vec2 currTexcoords=texCoords;
    float currDepthMapValue=texture(parallaxTexture,texCoords).r;
    while(currLayerDepth<currDepthMapValue)    {
        currTexcoords-=deltaTexcoords;
        currDepthMapValue=texture(parallaxTexture,currTexcoords).r;
        currLayerDepth+=layerDepth;
    }

    vec2 preTexcoords=currTexcoords+deltaTexcoords;
    float afterDepth=currLayerDepth-currDepthMapValue;
    float preDepth=texture(parallaxTexture,preTexcoords).r-(currLayerDepth-layerDepth);
    float weight=afterDepth/(afterDepth+preDepth);
    //vec2 finalTexCoords=weight*preTexcoords+(1.0-weight)*currTexcoords;
    vec2 finalTexCoords=weight*currTexcoords+(1.0-weight)*preTexcoords;//为什么应该是上一条语句才能实现线性变换
    return finalTexCoords;
}
void main()
{
    
    vec3 dirTocamera=normalize(fs_in.TangentViewPos-fs_in.TangentFragPos);
    vec2 texcoord=ParallaxMapping(fs_in.TexCoords,dirTocamera);
    vec3 uNormal=texture(normalTexture,texcoord).rgb;
    uNormal=uNormal*2.0-1.0;
    if(texcoord.x > 1.0 || texcoord.y > 1.0 || texcoord.x < 0.0 || texcoord.y < 0.0)
	discard;
    vec3 finalResult=ambientColor+CalLightPoint(lightP0,uNormal,dirTocamera,texcoord);
    FragColor=vec4(finalResult,1.0f);
}
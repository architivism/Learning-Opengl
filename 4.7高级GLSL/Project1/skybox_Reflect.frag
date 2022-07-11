#version 330 core
in vec3 Position;
in vec3 Normals;

out vec4 FragColor;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
   float radio=1.00/1.52;
   vec3 I=normalize(Position-cameraPos);
   //vec3 R=reflect(I,normalize(Normals));
   vec3 R = refract(I, normalize(Normals), radio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
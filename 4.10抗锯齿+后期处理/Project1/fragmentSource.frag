 #version 330 core
out vec4 FragColor;
//in vec4 vexterColor;

uniform vec3 objcolor;
uniform vec3 lightcolor;
void main()
{
 
  FragColor=vec4(lightcolor*objcolor,1.0f);
}
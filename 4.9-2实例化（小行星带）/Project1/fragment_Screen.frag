#version 330 core
									
in vec4 vertexColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
out vec4 FragColor;								   
void main()
{             
    float gamma=2.2;
    FragColor = texture(screenTexture, TexCoords);
    FragColor.rgb=pow(FragColor.rgb,vec3(1.0/gamma));
}


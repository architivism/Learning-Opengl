#version 330 core
									
in vec4 vertexColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
out vec4 FragColor;

const float offset=1.0/300;

void main()
{   
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    vec3 sampleTex[9];
    for(int i=0;i<9;i++)
    {
    sampleTex[i]=vec3(texture(screenTexture,TexCoords+offsets[i]));
    }
    vec3 col;
    for(int i;i<9;i++)
    {
    col+=sampleTex[i]*kernel[i];
    }
    //FragColor = texture(screenTexture, TexCoords);
	//float average=(0.2126*FragColor.x+.7152*FragColor.y+0.0722*FragColor.z)/3.0;
	FragColor=vec4(col,1.0);
}

#version 330 core
layout(triangles)in;
layout(line_strip,max_vertices=6)out;

in VS_OUT{
  vec3 Normal;
  }gs_in[];
uniform mat4 model;
layout(std140)uniform Matrices{
  mat4 projection;
  mat4 view;
};
const float MAGNITUDE=0.4;

void GenerateLine(mat3 matrixNormal,int index)
{
   gl_Position=projection*view*model*gl_in[index].gl_Position;
   EmitVertex();

   vec4 ptNormal=view*model*gl_in[index].gl_Position+vec4(normalize(matrixNormal*gs_in[index].Normal)*MAGNITUDE,0.0f);
   gl_Position=projection*ptNormal;
   EmitVertex();

   EndPrimitive();
}

void main()
{
  mat3 nMat=mat3(transpose(inverse(view*model)));
  GenerateLine(nMat,0);
  GenerateLine(nMat,1);
  GenerateLine(nMat,2);
}
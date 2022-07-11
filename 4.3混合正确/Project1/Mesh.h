#pragma once
#include <string>
#include <vector>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};
class Mesh
{
public:
	std::vector<Vertex> vertexs;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int VAO;
	Mesh(float _vertexs[]);
	Mesh(std::vector<Vertex> _vertexs,std::vector<unsigned int>_indices,std::vector<Texture>);
	void DrawElements(Shader &shader);
	void DrawArray(Shader shader, int diffuse, int specular);
	void DrawSliceArray(Shader shader, int diffuse, int specular);
public:
	unsigned int VBO, EBO;
	void setupMesh();
};


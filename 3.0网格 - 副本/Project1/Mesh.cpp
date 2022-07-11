#define GLFW_STATIC
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Mesh.h"
#include "Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Material.h"


Mesh::Mesh(float _vertexs[])
{
	vertexs.resize(36);
	memcpy(&vertexs[0], _vertexs, 36 * 8 * sizeof(float));
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertexs, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
{
	vertexs = _vertexs;
	indices = _indices;
	textures = _textures;
	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	//glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexs)*vertexs.size(),&vertexs[0],GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(indices) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6*sizeof(float)));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture.diffuse")
		{
			glActiveTexture(GL_TEXTURE2);
			glUniform1f(glGetUniformLocation(shader.ID, "material.diffuse"), 2);
			glBindTexture(GL_TEXTURE_BUFFER, textures[i].id);
		}
		else if (textures[i].type == "texture.specualr")
		{
			glActiveTexture(GL_TEXTURE2);
			glUniform1f(glGetUniformLocation(shader.ID, "material.specular"), 10);
			glBindTexture(GL_TEXTURE_BUFFER,textures[i].id);
		}
	}
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES,0,36);
	//glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
	glActiveTexture(GL_TEXTURE0);
}


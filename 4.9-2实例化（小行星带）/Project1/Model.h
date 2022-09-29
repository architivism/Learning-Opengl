#pragma once
#include <vector>
#include <string>
#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
class Model
{
public:
	/*  ����   */
	Model(std::string path);
	void Draw(Shader shader);
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
private:
	/*  ģ������  */
	
	std::string directory;
	
	/*  ����   */
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
};

#pragma once
#include <vector>
#include <string>
#include "Mesh.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

using namespace std;

class Model
{
public:
	Model(std::string _path);
	void Draw(Shader shader);
private:
	std::vector<Mesh>meshes;
	std::string directory;
	std::vector<Texture>textures_load;
	void loadModel(std::string path);
	void processNode(aiNode *node,const aiScene *scene);
	Mesh processMesh(aiMesh* mesh,const aiScene* scene);
	std::vector<Texture>loadMaterialTexture(aiMaterial*mat,aiTextureType type,std::string typeName );
	unsigned int TextureFromFile(const char* _path, const string& directory);
};


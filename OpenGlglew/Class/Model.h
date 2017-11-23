#ifndef MODEL_H 
#define MODEL_H


#include <glad/glad.h> 

//#include "SOIL/SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	vector<Texture> mTextures_load;
	vector<Mesh> mMesh;
	string mDirectory;
	bool gammaCorrection;

public:
	Model();
	virtual ~Model();

	void CreateModel(string const& path, bool gamma = false);

	void Draw(Shader shader);

private:
	void loadModel(string const& path);

	void processNode(aiNode *node, const aiScene* Scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* Scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = true);
};



#endif
#ifndef MESH_H
#define MESH_H

#include "assimp/Importer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex{
	// 坐标
	glm::vec3 Position;
	// 法向量
	glm::vec3 Normal;
	// 纹理坐标
	glm::vec2 TexCoords;
	//
	//glm::vec3 Tangent;
	//
	//glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string Type;
	aiString Path;
};
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	/*  网格数据  */
	vector<Vertex> mVertices;
	vector<unsigned int> mIndices;
	vector<Texture> mTextures;
	unsigned int VAO;

	void CreateMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void Draw(Shader shader);

private:
	unsigned int VBO, EBO;

	void setupMesh();

};

#endif
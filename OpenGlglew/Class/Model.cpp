#include "stdafx.h"
#include "Model.h"

Model::Model()
{

}
Model::~Model()
{

}
void Model::CreateModel(string const& path, bool gamma /* = false */)
{ 
	gammaCorrection = gamma;
	this->loadModel(path);
}
void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < mMesh.size();i++)
	{
		mMesh[i].Draw(shader);
	}
}
void Model::loadModel(string const& path)
{
	Assimp::Importer pImporter;
	const aiScene* pScene = pImporter.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_RemoveComponent);
	 
	if (!pScene || pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
	{
	//	cout << "ERROR::ASSIMP:: " << pImporter.GetErrorString() << endl;
		std::cout << "Model could not be imported: " << std::endl;
		std::cout << pImporter.GetErrorString() << std::endl;
		return;
	}
	mDirectory = path.substr(0, path.find_last_of('/'));
	processNode(pScene->mRootNode, pScene);
}
void Model::processNode(aiNode *node, const aiScene* Scene)
{   
	//处理节点的所有网格，
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
   {
		aiMesh* pAimesh = Scene->mMeshes[node->mMeshes[i]];
		mMesh.push_back(processMesh(pAimesh, Scene));
   }
	// 对他的子节点递归处理
	for (unsigned int j = 0; j < node->mNumChildren;j++)
   {
		processNode(node->mChildren[j], Scene);
   }
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* Scene)
{
	vector<Vertex> pVertexs;
	vector<unsigned int> pIndices;
	vector<Texture> pTextures;

	for (unsigned int i = 0; i < mesh->mNumVertices;i++)
	{
		Vertex pVertex;
		glm::vec3 pVector;
		// 顶点数据
		pVector.x = mesh->mVertices[i].x;
		pVector.y = mesh->mVertices[i].y;
		pVector.z = mesh->mVertices[i].z;
		pVertex.Position = pVector;

		// 法线
		if (mesh->mNormals != NULL)
		{
			pVector.x = mesh->mNormals[i].x;
			pVector.y = mesh->mNormals[i].y;
			pVector.z = mesh->mNormals[i].z;
			pVertex.Normal = pVector;
		}
		else
		{
			pVertex.Normal = glm::vec3(0.0f,0.0f,0.0f);
		}
        // 纹理坐标
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			pVertex.TexCoords = vec;

		}
		else
		{
			pVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		//pVector.x = mesh->mTangents[i].x;
		//pVector.y = mesh->mTangents[i].y;
		//pVector.z = mesh->mTangents[i].z;

		//pVertex.Tangent = pVector;

		//pVector.x = mesh->mBitangents[i].x;
		//pVector.y = mesh->mBitangents[i].y;
		//pVector.z = mesh->mBitangents[i].z;

		//pVertex.Bitangent = pVector;

		pVertexs.push_back(pVertex);
	}
	// 索引
	for (unsigned int j = 0; j < mesh->mNumFaces;j++)
	{
		aiFace pFace = mesh->mFaces[j];
		for (unsigned int k = 0; k < pFace.mNumIndices;k++)
		{
			pIndices.push_back(pFace.mIndices[k]);
		}
	}
	//aiMaterial* pMaterial = Scene->mMaterials[mesh->mMaterialIndex];

	//vector<Texture> diffuseMaps = loadMaterialTextures(pMaterial, aiTextureType_DIFFUSE, "texture_diffuse");

	//vector<Texture> specularMaps = loadMaterialTextures(pMaterial, aiTextureType_SPECULAR, "texture_specular");

	//vector<Texture> normalMaps = loadMaterialTextures(pMaterial, aiTextureType_HEIGHT, "texture_normal");

	//vector<Texture> heightMaps = loadMaterialTextures(pMaterial, aiTextureType_AMBIENT, "texture_height");

	//pTextures.insert(pTextures.end(), heightMaps.begin(), heightMaps.end());
	// 处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		/* aiTextureType_AMBIENT  漫反射贴图 */
		aiMaterial* material = Scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
		pTextures.insert(pTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = this->loadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		pTextures.insert(pTextures.end(), specularMaps.begin(), specularMaps.end());
	}

	Mesh pMesh = Mesh::Mesh();
	pMesh.CreateMesh(pVertexs, pIndices, pTextures);
	return pMesh;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> pTextures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool pSkip = false;
		for (unsigned int j = 0; j < mTextures_load.size();j++)
		{
			if (std::strcmp(mTextures_load[j].Path.C_Str(),str.C_Str())== 0)
			{
				pTextures.push_back(mTextures_load[j]);
				pSkip = true;
				break;
			}
		}
		if (!pSkip)
		{
			Texture pTexture;
			pTexture.id = TextureFromFile(str.C_Str(), this->mDirectory);
			pTexture.Type = typeName;
			pTexture.Path = str;
			pTextures.push_back(pTexture);
			mTextures_load.push_back(pTexture);
		}
    }
	return pTextures;
}
unsigned int Model::TextureFromFile(const char *path, const string &directory, bool gamma /* = true */)
{
	string filename = string(path);
	filename = mDirectory + '/' + filename;
	unsigned int pTextureID;
	glGenTextures(1, &pTextureID);

	int width, height, nrComponents;
	unsigned char* pData = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (pData)
	{
		GLenum format;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, pTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(pData);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(pData);

	}
	return pTextureID;
}
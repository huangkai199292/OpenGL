#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Class/Shader.h"
#include "iostream"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"

class Scene
{
public:
	GLint shaderProgram; //  ��ɫ��
	Camera mCamera;      //  �����
	GLint shaderLight;   // ��Դ��ɫ��

	GLint shaderModel;   // ģ����ɫ��
	GLint shaderSkybox;  // ��պ�����ɫ��
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2, diffuseMap;
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	glm::mat4 trans;
	Shader mshader;
	Shader Lightshader;
	Shader mModelShader;
	Shader mSkyboxShader; 
	unsigned int lightVAO;
	unsigned int cubeVAO;
	Model mModel;
public:
	Scene();
	virtual ~Scene();

	void CreateShader();
	void Draw();
	void DeleteShader();

	void CreateColor();
	void DrawColor();
	void DeleteColor();
	void WindowInput(GLFWwindow *window);

	void CreateModel();
	void DrawModel();
	void DeleteModel();
	unsigned int loadTexture(const char* path);

	void CreateSkybox();
	void DeleteSkybox();
	unsigned int loadCubemap(vector<std::string> faces); // ��պ��� ����ͼƬ
};
#endif
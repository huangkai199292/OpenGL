#ifndef SCENE_H
#define SCENE_H

#include "stdafx.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Class/Shader.h"
#include "iostream"
#include "stb_image.h"

class Scene
{
public:
	GLint shaderProgram;
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2;
public:
	Scene();
	virtual ~Scene();

	void CreateShader();
	void Draw();
	void DeleteShader();
};
#endif
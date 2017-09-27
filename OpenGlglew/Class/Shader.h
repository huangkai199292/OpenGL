
#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"

class Shader
{
public:
	unsigned int ID;
	GLint shaderProgram;

	Shader(const char* vertexPath, const char* fragmentPath);
	// 使用/激活
	GLint GetShader();
	// unform 工具
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, bool value) const;
	void setFloat(const std::string &name, bool value) const;
	GLint LoadShader(GLenum ShaderType, const char* pScourue);
	GLint CreatProgram(const char* vertexSource, const char* fragmentSouece);
};

#endif
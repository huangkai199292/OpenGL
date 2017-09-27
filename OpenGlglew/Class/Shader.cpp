#include "stdafx.h"
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ��֤ ifstream ����������쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		// ��ȡ�Ļ������ݵ���������
		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();
		// �ر��ļ�����
		vShaderFile.close();
		fShaderFile.close();
		// ת������������string��
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	shaderProgram = this->CreatProgram(vShaderCode, fShaderCode);

}
// ��ɫ��
GLint Shader::LoadShader(GLenum ShaderType, const char* pScourue)
{
	// ������ɫ��
	GLuint vertexShader = glCreateShader(ShaderType);
	if (vertexShader)
	{
		// ����ɫ��Դ�븽�ӵ���ɫ��������
		glShaderSource(vertexShader, 1, &pScourue, NULL);
		glCompileShader(vertexShader);
		GLint success = 0;
		// ������ɹ���
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint infoLen = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLen);
			if (!infoLen)
			{
				char* buf = (char*)malloc(infoLen);
				if (buf)
				{
					glGetShaderInfoLog(vertexShader, infoLen, NULL, buf);
					printf("Could not compile shader%d:\n%s\n", ShaderType, buf);
					free(buf);
				}
				glDeleteShader(vertexShader);
				vertexShader = 0;
			}
		}
	}
	return vertexShader;
}
GLint Shader::CreatProgram(const char* vertexSource, const char* fragmentSouece)
{
	// ������ɫ��
	GLint vertexShader = this->LoadShader(GL_VERTEX_SHADER, vertexSource);
	if (!vertexShader)
	{
		return 0;
	}
	// ƬԪ��ɫ��
	GLint fragmentShader = this->LoadShader(GL_FRAGMENT_SHADER, fragmentSouece);
	if (!fragmentShader)
	{
		return 0;
	}

	GLint shaderProgram = glCreateProgram();
	if (shaderProgram)
	{
		// ���Ӷ���shader
		glAttachShader(shaderProgram, vertexShader);
		// ����ƬԪshader
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		GLint LinkStatus = GL_FALSE;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &LinkStatus);
		if (LinkStatus == GL_FALSE)
		{
			GLint bufLenght = 0;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &bufLenght);
			if (!bufLenght)
			{
				char* buf = (char*)malloc(bufLenght);
				if (buf)
				{
					glGetProgramInfoLog(shaderProgram, bufLenght, NULL, buf);
					printf("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(shaderProgram);
			shaderProgram = 0;
		}
	}
	return shaderProgram;

}
GLint Shader::GetShader()
{
	if (shaderProgram)
	{
		return shaderProgram;
	}
	return 0;
}
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, bool value)const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, bool value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
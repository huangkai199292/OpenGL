#include "stdafx.h"
#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 保证 ifstream 对象可以抛异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		// 读取的缓冲内容到数据流中
		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();
		// 关闭文件处理
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到是string中
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
	ID = shaderProgram;
}
// 着色器
GLint Shader::LoadShader(GLenum ShaderType, const char* pScourue)
{
	// 创建着色器
	GLuint vertexShader = glCreateShader(ShaderType);
	if (vertexShader)
	{
		// 把着色器源码附加到着色器对象上
		glShaderSource(vertexShader, 1, &pScourue, NULL);
		glCompileShader(vertexShader);
		GLint success = 0;
		// 检测编译成功否
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
	// 顶点着色器
	GLint vertexShader = this->LoadShader(GL_VERTEX_SHADER, vertexSource);
	if (!vertexShader)
	{
		return 0;
	}
	// 片元着色器
	GLint fragmentShader = this->LoadShader(GL_FRAGMENT_SHADER, fragmentSouece);
	if (!fragmentShader)
	{
		return 0;
	}

	GLint shaderProgram = glCreateProgram();
	if (shaderProgram)
	{
		// 连接顶点shader
		glAttachShader(shaderProgram, vertexShader);
		// 连接片元shader
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
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
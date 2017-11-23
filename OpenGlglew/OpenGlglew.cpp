// OpenGlglew.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Class/Shader.h"
#include "iostream"
#include "Class/Scene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//����������Ϊ�رգ�����ѭ��  
		glfwSetWindowShouldClose(window, true);
	}
	 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// ��ɫ��
GLint LoadShader(GLenum ShaderType,const char* pScourue)
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
GLint CreatProgram(const char* vertexSource,const char* fragmentSouece)
{
	// ������ɫ��
	GLint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexSource);
	if (!vertexShader)
	{
		return 0;
	}
    // ƬԪ��ɫ��
	GLint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentSouece);
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

int main()
{
 
 
	//glfw��ʼ��  
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfw��������  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("��������ʧ��");
		//��ֹ  
		glfwTerminate();
		return -1;
	}
	//��ʾ����  
	glfwMakeContextCurrent(window);
	//���ûص��������ڴ�С�����󽫵��øûص�����  
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad��ʼ��  
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("����ʧ��");
		return -1;
	}
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
 
	//GLint shaderProgram = CreatProgram(vertexShaderSource, fragmentShaderSource);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//float vertices[] = {
	//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, -0.5f, 0.0f, // ���½�
	//	-0.5f, 0.5f, 0.0f   // ���Ͻ� 
	//};
	//unsigned int indices[] = { // ע��������0��ʼ! 
	//	0, 1, 3, // ��һ��������
	//	1, 2, 3  // �ڶ���������
	//};

	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO); // ����һ���µĻ���������
	//// �� ��������
	//glBindVertexArray(VAO);
	//// �Ѷ������鸴�Ƶ������У�VBO ���㻺�����
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);  // ������������ VBO�� ��������
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �򻺳��������и��ƶ�������


	//GLuint EBO;
	//glGenBuffers(1,&EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	Scene mScene = Scene::Scene();
	mScene.CreateModel();
	// ʹ��ѭ���ﵽѭ����ȾЧ��  
	while (!glfwWindowShouldClose(window))
	{
		//�Զ��������¼�  
		processInput(window);
		mScene.WindowInput(window);
		mScene.DrawModel();		
		
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//������������������ʾ�հ�  
		glfwSwapBuffers(window);
		//��������¼�,�����޷��Դ��ڽ��н���  
		glfwPollEvents();
	}
	mScene.DeleteModel();
	//��ֹ��Ⱦ �رղ�����glfw������Դ  
	glfwTerminate();
	return 0;
}
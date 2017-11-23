// OpenGlglew.cpp : 定义控制台应用程序的入口点。
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
		//将窗口设置为关闭，跳出循环  
		glfwSetWindowShouldClose(window, true);
	}
	 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// 着色器
GLint LoadShader(GLenum ShaderType,const char* pScourue)
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
GLint CreatProgram(const char* vertexSource,const char* fragmentSouece)
{
	// 顶点着色器
	GLint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexSource);
	if (!vertexShader)
	{
		return 0;
	}
    // 片元着色器
	GLint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentSouece);
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

int main()
{
 
 
	//glfw初始化  
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfw创建窗口  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("创建窗口失败");
		//终止  
		glfwTerminate();
		return -1;
	}
	//显示窗口  
	glfwMakeContextCurrent(window);
	//设置回调，当窗口大小调整后将调用该回调函数  
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glad初始化  
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("加载失败");
		return -1;
	}
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
 
	//GLint shaderProgram = CreatProgram(vertexShaderSource, fragmentShaderSource);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//float vertices[] = {
	//	0.5f, 0.5f, 0.0f,   // 右上角
	//	0.5f, -0.5f, 0.0f,  // 右下角
	//	-0.5f, -0.5f, 0.0f, // 左下角
	//	-0.5f, 0.5f, 0.0f   // 左上角 
	//};
	//unsigned int indices[] = { // 注意索引从0开始! 
	//	0, 1, 3, // 第一个三角形
	//	1, 2, 3  // 第二个三角形
	//};

	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO); // 创建一个新的缓冲区对象
	//// 绑定 顶点数组
	//glBindVertexArray(VAO);
	//// 把顶点数组复制到缓冲中（VBO 顶点缓冲对象）
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);  // 将缓冲区对象 VBO和 缓冲区绑定
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 向缓冲区对象中复制顶点数据


	//GLuint EBO;
	//glGenBuffers(1,&EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	Scene mScene = Scene::Scene();
	mScene.CreateModel();
	// 使用循环达到循环渲染效果  
	while (!glfwWindowShouldClose(window))
	{
		//自定义输入事件  
		processInput(window);
		mScene.WindowInput(window);
		mScene.DrawModel();		
		
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//交互缓冲区，否则显示空白  
		glfwSwapBuffers(window);
		//输入输出事件,否则无法对窗口进行交互  
		glfwPollEvents();
	}
	mScene.DeleteModel();
	//终止渲染 关闭并清理glfw本地资源  
	glfwTerminate();
	return 0;
}
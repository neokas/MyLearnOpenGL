#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "MyShader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //每次窗口大小被调整时,调整视口大小
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//const char *fragmentShaderSource2 = 
//	"#version 330 core\n"
//	"out vec4 FragColor;\n"
//	"int vec4 ourColor;\n"
//	"void main()\n"
//	"{\n"
//	"   FragColor = vec4(ourColor,1.0);\n"
//	"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //副版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //注册回调函数：每次窗口大小被调整时,调整视口大小

	//初始化GLAD，用于管理OpenGL的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//顶点
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	//创建VBO VAO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //绑定VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);   //绑定缓冲VBO到GL_ARRAY_BUFFER上  顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //复制顶点数据 到 缓冲内存中
	//位置信息
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色信息
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader myShader("E:/桌面/learnopengl/Shaders/1.vs", "E:/桌面/learnopengl/Shaders/1.fs");

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//输入
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f); //设置清屏的颜色
		glClear(GL_COLOR_BUFFER_BIT); //清屏

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //线框模式
		


		myShader.use();
		glBindVertexArray(VAO);
		float offset = 0;
		myShader.setFloat("xOffset", offset);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);


		//检查并调用事件，交换缓冲；
		glfwPollEvents(); //检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
		glfwSwapBuffers(window); //交换颜色缓冲,它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
	
	}

	//删除VAO VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate(); //释放资源 
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//设置Viewport(视口：渲染窗口的大小)
	glViewport(0, 0, width, height); //前两个参数控制窗口左下角的位置，后两个参数控制窗口的宽度和高度。
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

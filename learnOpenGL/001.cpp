#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //每次窗口大小被调整时,调整视口大小

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //副版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//初始化GLAD，用于管理OpenGL的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//设置Viewport(视口：渲染窗口的大小)，
	glViewport(0, 0, 800, 600);  //前两个参数控制窗口左下角的位置，后两个参数控制窗口的宽度和高度。
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //注册回调函数：每次窗口大小被调整时,调整视口大小

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window); //交换颜色缓冲
		glfwPollEvents(); //检测触发事件
	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
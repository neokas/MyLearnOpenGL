#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //ÿ�δ��ڴ�С������ʱ,�����ӿڴ�С

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //���汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ

	//��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //ע��ص�������ÿ�δ��ڴ�С������ʱ,�����ӿڴ�С

	//��ʼ��GLAD�����ڹ���OpenGL�ĺ���ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window); //������ɫ����,����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents(); //�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
	}

	glfwTerminate(); //�ͷ���Դ 
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//����Viewport(�ӿڣ���Ⱦ���ڵĴ�С)
	glViewport(0, 0, width, height); //ǰ�����������ƴ������½ǵ�λ�ã��������������ƴ��ڵĿ�Ⱥ͸߶ȡ�
}
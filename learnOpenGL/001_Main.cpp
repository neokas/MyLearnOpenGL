#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "MyShader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //ÿ�δ��ڴ�С������ʱ,�����ӿڴ�С
void processInput(GLFWwindow *window);

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

	//����
	float vertices[] = {
		// λ��                // ��ɫ           // ��������
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//����VBO VAO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO); //��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);   //�󶨻���VBO��GL_ARRAY_BUFFER��  ���㻺�����Ļ���������GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //���ƶ������� �� �����ڴ���

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//λ����Ϣ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ��Ϣ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//����������Ϣ
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader myShader("E:/����/learnopengl/Shaders/1.vs", "E:/����/learnopengl/Shaders/1.fs");

	//����
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ���ز���������
	int width, height, nrChannels;
	unsigned char *data = stbi_load("E:/����/learnopengl/images/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//����
		glGenerateMipmap(GL_TEXTURE_2D); //�Զ����ɶ༶��Զ����
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); //�������������Ӧ�Ķ༶��Զ������ͷ�ͼ����ڴ�

	

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//����
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f); //������������ɫ
		glClear(GL_COLOR_BUFFER_BIT); //����

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ
		
	    glActiveTexture(GL_TEXTURE0); //�ڰ�����֮ǰ�ȼ�������Ԫ
		glBindTexture(GL_TEXTURE_2D, texture);

		myShader.use();
		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);


		//��鲢�����¼����������壻
		glfwSwapBuffers(window); //������ɫ����,����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwPollEvents(); //�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����

	}

	//ɾ��VAO VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate(); //�ͷ���Դ 
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//����Viewport(�ӿڣ���Ⱦ���ڵĴ�С)
	glViewport(0, 0, width, height); //ǰ�����������ƴ������½ǵ�λ�ã��������������ƴ��ڵĿ�Ⱥ͸߶ȡ�
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

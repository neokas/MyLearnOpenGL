#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //ÿ�δ��ڴ�С������ʱ,�����ӿڴ�С
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
const char *fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(ourColor,1.0);\n"
	"}\n\0";
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

	//����������ɫ��
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//�������ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //��������Ҫ�������ɫ�����󣬴��ݵ�Դ���ַ���������������ɫ��Դ�룬null)
	glCompileShader(vertexShader);
	//��ȡ������Ϣ
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//����Ƭ����ɫ��1
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	////����Ƭ����ɫ��2
	//unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	//glCompileShader(fragmentShader2);


	//��ɫ���������
	unsigned int shaderProgram = glCreateProgram();
	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);   //���Ӷ�����ɫ��
	glAttachShader(shaderProgram, fragmentShader); //����Ƭ����ɫ��
	glLinkProgram(shaderProgram); //���ӵ�����

	//glAttachShader(shaderProgram2, vertexShader);   //���Ӷ�����ɫ��
	//glAttachShader(shaderProgram2, fragmentShader2); //����Ƭ����ɫ��
	//glLinkProgram(shaderProgram2); //���ӵ�����

	glDeleteShader(vertexShader); //�����Ӻ�ɾ����ɫ������
	glDeleteShader(fragmentShader);
	/*glDeleteShader(fragmentShader2);*/
	//��ȡ������Ϣ
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	

	//����
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	//����VBO VAO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //��VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);   //�󶨻���VBO��GL_ARRAY_BUFFER��  ���㻺�����Ļ���������GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //���ƶ������� �� �����ڴ���
	//λ����Ϣ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ��Ϣ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/



	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//����
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f); //������������ɫ
		glClear(GL_COLOR_BUFFER_BIT); //����

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //�߿�ģʽ
		
		//��ɫ���е�uniform
		/*glUseProgram(shaderProgram2);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);


		//��鲢�����¼����������壻
		glfwPollEvents(); //�����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����
		glfwSwapBuffers(window); //������ɫ����,����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
	
	}

	//ɾ��VAO VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


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

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;


//function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;
//bước 0.0: chuẩn bị shader
//Tam giác 1
const GLchar* vertexShaderSourceLeft = "#version 330 core\n"
"layout (location=0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position= vec4(position.x,position.y,position.z,1);\n"
"}\0";
const GLchar* fragmentShaderSourceLeft = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color= vec4(0.0f,1.0f,1.0f,1.0f);\n"
"}\0";

//Tam giác 2
const GLchar* vertexShaderSourceRight = "#version 330 core\n"
"layout (location=0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position= vec4(position.x,position.y,position.z,1);\n"
"}\0";
const GLchar* fragmentShaderSourceRight = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color= vec4(1.0f,1.0f,0.0f,0.0f);\n"
"}\0";

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Tạo 1 cửa sổ GLFWwindow 
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bai Tap 03 - Hello Triangle (Powered By Thang Vu 181864)", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	//Đặt biến glewExperimental về true  (bắt buộc)
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Định nghĩa kích thước viewport
	 // Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);    // lấy kích thước framebuffer   (chú ý)
	glViewport(0, 0, width, height);;

	////// bước 0.1 Build và biên dịch shader program
	GLint success;
	GLchar infoLog[512];
	// Tam giác 1
	// Vertex shader
	GLuint vertexShaderLeft = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderLeft, 1, &vertexShaderSourceLeft, NULL);
	glCompileShader(vertexShaderLeft);
	// Check for compile time errors
	glGetShaderiv(vertexShaderLeft, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderLeft, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShaderLeft = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderLeft, 1, &fragmentShaderSourceLeft, NULL);
	glCompileShader(fragmentShaderLeft);
	// Check for compile time errors
	glGetShaderiv(fragmentShaderLeft, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderLeft, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	GLuint shaderProgramLeft = glCreateProgram();
	glAttachShader(shaderProgramLeft, vertexShaderLeft);
	glAttachShader(shaderProgramLeft, fragmentShaderLeft);
	glLinkProgram(shaderProgramLeft);
	// Check for linking errors
	glGetProgramiv(shaderProgramLeft, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramLeft, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderLeft);
	glDeleteShader(fragmentShaderLeft);
	// Tam giác 2
	// Vertex shader
	GLuint vertexShaderRight = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderRight, 1, &vertexShaderSourceRight, NULL);
	glCompileShader(vertexShaderRight);
	// Check for compile time errors
	glGetShaderiv(vertexShaderRight, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderRight, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShaderRight = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRight, 1, &fragmentShaderSourceRight, NULL);
	glCompileShader(fragmentShaderRight);
	// Check for compile time errors
	glGetShaderiv(fragmentShaderRight, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderRight, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	GLuint shaderProgramRight = glCreateProgram();
	glAttachShader(shaderProgramRight, vertexShaderRight);
	glAttachShader(shaderProgramRight, fragmentShaderRight);
	glLinkProgram(shaderProgramRight);
	// Check for linking errors
	glGetProgramiv(shaderProgramRight, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramRight, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShaderRight);
	glDeleteShader(fragmentShaderRight);

	//bước 1: khai báo vertex input (vertex data)
	GLfloat vertices_left[] = {
		// tam giac 1
		-0.8f,-0.4f,0.0f,  //bottom-left
		0.0f,-0.4f,0.0f,   //bottom right
		-0.4f,0.4f,0.0f,    //Top Left 
	};
	GLfloat vertices_right[] = {
		// tam giac 2
		0.0f,-0.4f,0.0f,  //bottom-left
		0.8f,-0.4f,0.0f,   //bottom right
		0.4f,0.4f,0.0f,    //Top Left
	};
	//Bước 2: Khởi tạo VBO, VAO
	//b2.1 VAO
	GLuint VAO[2];
	GLuint VBO[2];
	// Tam giác 1
	glGenVertexArrays(1, &VAO[0]);
	//bind VAO
	glBindVertexArray(VAO[0]);
	//b2.2 VBO
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // liên kết (bind) VBO
	//sao chep du lieu vertices vao bo nho
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_left), vertices_left, GL_STATIC_DRAW);

	//set attribute point
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO , cho phép gọi hàm glVertexAttribPointer trong VBO
	//unbind VAO
	glBindVertexArray(0);

	// Tam giác 2 
	glGenVertexArrays(1, &VAO[1]);
	//bind VAO
	glBindVertexArray(VAO[1]);
	//b2.2 VBO
	glGenBuffers(1, &VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); // liên kết (bind) VBO
	//sao chep du lieu vertices vao bo nho
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_right), vertices_right, GL_STATIC_DRAW);

	//set attribute point
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO , cho phép gọi hàm glVertexAttribPointer trong VBO
	//unbind VAO
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// check sự kiện  (ấn nút bàn phím, chuột,...)
		glfwPollEvents();
		//Render
		//xóa color buffer
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Buoc 3 Vẽ hình 1 hình tam giác

		// Vẽ tam giác 1
		glUseProgram(shaderProgramLeft);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// Vẽ tam giác 2
		glUseProgram(shaderProgramRight);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		///swap
		glfwSwapBuffers(window);
	}
	//Terminate GLFW, xóa và dọn dẹp tài nguyên sau khi thoát
	glfwTerminate();
	return 0;

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

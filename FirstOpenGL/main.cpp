#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <intrin.h>

#define ASSERT(X) do { if(!(X) )__debugbreak();}while(0)
#define GLCall(X) ClearGLError();\
X;\
ASSERT(PrintGLError(__FILE__, #X,__LINE__));


static struct Shader {
	std::string vertexShader;
	std::string fragmentShader;
};

static void ClearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool PrintGLError(const char* fileName, const char* functionName, const int lineNumber)
{
	unsigned int err;
	std::string ErrorString;
	while ((err = glGetError()) != GL_NO_ERROR) {
		switch (err) {
		case GL_INVALID_ENUM: ErrorString = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: ErrorString = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: ErrorString = "GL_INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW: ErrorString = "GL_STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW: ErrorString = "GL_STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY: ErrorString = "GL_OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << "Error : [ " << ErrorString << " ] File Name [ " << fileName << " ] Function [ "<< functionName << " ] Line Number [ " << lineNumber << " ]" <<  std::endl;
		return false;
	}
}

static Shader ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	std::string line;
	enum class ShaderType { VERTEX, FRAGMENT };
	ShaderType type;

	std::ostringstream shaderArray[2];
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			shaderArray[(int)type] << line << "\n";
		}
	}	
	return { shaderArray[(int)ShaderType::VERTEX].str(), shaderArray[(int)ShaderType::FRAGMENT].str() };
}

unsigned int CompileShader(const std::string& source, int shaderType)
{
	unsigned int id;

	id = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		fprintf(stderr, "%s Compile Err: %s\n", shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
		return -2;
	}
	else
		fprintf(stderr, "%s shader is compiled\n", shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment");
	return id;
}

unsigned int CreateShader(const std::string& vshader, const std::string& fshader)
{
	unsigned int program = glCreateProgram();
	unsigned int vid = CompileShader(vshader, GL_VERTEX_SHADER);
	unsigned int fid = CompileShader(fshader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vid);
	glAttachShader(program, fid);

	glLinkProgram(program);
	//glValidateProgram(program);

	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		fprintf(stderr, "Link Err: %s\n", infoLog);
		return 0;
	}
	glDeleteShader(vid);
	glDeleteShader(fid);

	return program;
}

void KeyHandlerCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, KeyHandlerCB);

	/*init glew*/
	GLuint ret = glewInit();
	if (ret != GLEW_OK) {
		fprintf(stderr, "Err: %s\n", glewGetErrorString(ret));
		return 1;
	}
	else {
		fprintf(stderr, "Info: %s\n", glGetString(GL_VERSION));
	}

	unsigned int bufferid;
	unsigned int ibo;
	float points[] = {
		-0.5f, -0.5f,
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f 
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Shader shaders = ParseShader("Res/shaders/basic.shader");

	//std::cout << "Vertex shader\n";
	//std::cout << shaders.vertexShader << std::endl;

	//std::cout << "Fragment shader\n";
	//std::cout << shaders.fragmentShader << std::endl;

	int program = CreateShader(shaders.vertexShader, shaders.fragmentShader);
	glUseProgram(program);

	glGenBuffers(1, &bufferid);
	glBindBuffer(GL_ARRAY_BUFFER, bufferid);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/*set color*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		
		GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
		

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <intrin.h>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

static struct Shader {
	std::string vertexShader;
	std::string fragmentShader;
};

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(20);

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
	{
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

		int program = CreateShader(shaders.vertexShader, shaders.fragmentShader);
		glUseProgram(program);


		int location = glGetUniformLocation(program, "u_Color");

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexBuffer vb1(points, sizeof(points));
		IndexBuffer ib1(indices, 6);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
		glEnableVertexAttribArray(0);

		float redness = 0.05f, increment = 0.05;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/*set color*/
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			if (redness > 1.0)
				increment = -0.05;
			if (redness < 0.0)
				increment = 0.05;
			redness += increment;
			glUniform4f(location, redness, 0.3, 0.4, 1.0);
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));


			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
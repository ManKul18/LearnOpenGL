#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <intrin.h>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

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
	glfwSwapInterval(5);
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
	{ //open scope so that objects get destroyed automatically
		float points[] = {
			/* shape coordinates, texture coordinates*/
				-0.5f, -0.5f, 0.0f, 0.0f,
				-0.5f,  0.5f, 0.0f, 1.0f,
				 0.5f,  0.5f, 1.0f, 1.0f,
				 0.5f, -0.5f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Renderer rendrr;
		Shader shaders("Res/shaders/basic.shader");

		VertexArray va;
		VertexBufferLayout layout;
		Texture texture("Res/texture/mk.png");

		VertexBuffer vb1(points, sizeof(points));
		layout.Push(0.0f, 2);
		layout.Push(0.0f, 2);
		va.AddBuffer(vb1, layout);
		IndexBuffer ib1(indices, 6);
		texture.Bind();

		float redness = 0.05f, increment = 0.10f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/*set color and render*/
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (redness > 1.0f)
				increment = -0.10f;
			if (redness < 0.0f)
				increment = 0.10f;

			redness += increment;
			rendrr.Draw(va, ib1, shaders); //if called earlier shader is not bound
			shaders.SetUniform4f("u_Color", redness, 0.3f, 0.4f, 1.0f);
			shaders.SetUniform1i("u_Texture", 0);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
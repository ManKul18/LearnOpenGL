#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"

class Shader 
{
	enum class ShaderType { VERTEX, FRAGMENT };
private:
	unsigned int m_RendererID;

	void m_CreateShader(const std::string& vshader, const std::string& fshader);
	unsigned int m_CompileShader(const std::string& source, int shaderType);
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind();
	void Unbind();
	void SetUniform4f(const std::string uniformName, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
};

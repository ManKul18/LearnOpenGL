#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Utility.h"

using namespace std;

class Shader 
{
	enum class ShaderType { VERTEX, FRAGMENT };
private:
	unsigned int m_RendererID;
	map<string, int>m_UniformCache;
	void m_CreateShader(const string& vshader, const string& fshader);
	unsigned int m_CompileShader(const string& source, int shaderType);
public:
	Shader(const string& filePath);
	~Shader();

	void Bind(void);
	void Unbind(void);
	void SetUniform4f(const string uniformName, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);
	void SetUniform1i(const string uniformName, GLint i1);
};

#endif // !__SHADER_H__
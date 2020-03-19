#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalised;
	static unsigned int GetElementSize(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT: return sizeof(GLfloat); 
			case GL_UNSIGNED_INT: return sizeof(GLuint); 
			case GL_UNSIGNED_BYTE: return sizeof(GLbyte); 
			default:
				return 0;
		}
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout():m_Stride(0){}
	~VertexBufferLayout();

	void Push(float f, unsigned int count) { m_Elements.push_back({ GL_FLOAT, count, GL_FALSE }); m_Stride += count * sizeof(GLfloat); }
	void Push(unsigned int ui, unsigned int count) { m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE }); m_Stride += count * sizeof(GLuint); }
	void Push(unsigned char uc, unsigned int count) { m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE }); m_Stride += count * sizeof(GLbyte); }
	inline unsigned int GetStride() const { return m_Stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
};
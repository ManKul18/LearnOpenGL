#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

#include<GL/glew.h>

#include "Utility.h"

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;
};

#endif // !__INDEX_BUFFER_H__
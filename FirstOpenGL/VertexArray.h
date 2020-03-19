#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Utility.h"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vl);
	void Bind(void) const;
	void Unbind(void) const;
};

#endif // !__VERTEX_BUFFER_H__
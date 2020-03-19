#ifndef __VERTEX_BUFFER__
#define __VERTEX_BUFFER__

#include "Utility.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind(void) const;
	void Unbind(void) const;
};

#endif // !__VERTEX_BUFFER__

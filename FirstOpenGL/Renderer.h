#ifndef  __RENDERER_H__
#define __RENDERER_H__

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Utility.h"

class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& sh);
};

#endif // ! __RENDERER_H__
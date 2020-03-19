#include <iostream>

#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& sh)
{
	sh.Bind();
	va.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL));
}

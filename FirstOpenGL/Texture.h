#pragma once

#include <string>

#include "Utility.h"

using namespace std;


class Texture {
private:
	unsigned int m_RendererID;
	string m_fileName;
	unsigned char* m_TextureBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(string fileName);
	~Texture();

	void Bind(unsigned int slot=0) const;
	void Unbind() const;

	inline unsigned int GetWidth() { return m_Width; }
	inline unsigned int GetHeight() { return m_Height; }
};
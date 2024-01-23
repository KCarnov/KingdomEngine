#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Sources/lib/stb/stb_image.h"
#include <iostream>

class Texture
{
private:
	GLuint ID;
	int m_width, m_height, m_nrChannels, m_BPP;
	unsigned char* m_TextureData;
	const char* m_path;
public:
	Texture(const char* path);
	~Texture();

	void BindTexture(int slot = 0) const;
	void UnbindTexture() const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
};
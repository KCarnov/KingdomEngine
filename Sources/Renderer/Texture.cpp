#include "Texture.h"

Texture::Texture(const char* path)
	: ID(0), m_path(path), m_width(0), m_height(0), m_BPP(0), m_nrChannels(0), m_TextureData(nullptr)
{
	GLuint mID;
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	stbi_set_flip_vertically_on_load(true);
    m_TextureData = stbi_load(m_path, &m_width, &m_height, &m_nrChannels, 4);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (m_TextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_TextureData);
	ID = mID;
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::BindTexture(int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::UnbindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

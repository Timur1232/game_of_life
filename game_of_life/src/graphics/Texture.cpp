#include "Texture.h"
#include <GL/glew.h>

Texture::Texture(unsigned int id, int width, int height)
	: m_id(id), m_width(width), m_height(height) {}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
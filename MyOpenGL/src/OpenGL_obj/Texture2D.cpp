#include "pch.h"
#include"glad/glad.h"
#include"stb_image/stb_image.h"
#include "Texture2D.h"

Texture2D::Texture2D(const std::string& filePath)
	:m_FilePath(filePath)
{
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_2D, RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_TexData = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BBP, 4);
	if (m_TexData)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		GLenum format;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TexData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load Texture: " << m_FilePath.c_str() << std::endl;
	}
	if (m_TexData) { stbi_image_free(m_TexData); }

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &RendererID);
}

void Texture2D::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, RendererID);
}

void Texture2D::UnBind() const
{

}

#include "pch.h"
#include"glad/glad.h"
#include"stb_image/stb_image.h"
#include "Texture2D.h"

Texture2D::Texture2D(const std::string& filePath)
	:m_FilePath(filePath)
{

	stbi_set_flip_vertically_on_load(1);
	stbi_info(m_FilePath.c_str(), &m_Width, &m_Height, &m_BBP);
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	if(m_BBP == 1)
		m_TexData = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BBP,1);
	else 
		m_TexData = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BBP, 4);

	GLenum internalFormat, dataFormat;
	//动态计算mipmap层级 --from gemini 3.1pro
	GLsizei levels = (GLsizei)std::floor(std::log2(std::max(m_Width, m_Height))) + 1;
	if (m_BBP == 1)
	{
		internalFormat = GL_R8;
		dataFormat = GL_RED;
	}
	else
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}

	if (m_TexData)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		GLenum format;
		glTextureStorage2D(m_RendererID, levels, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_TexData);
		glGenerateTextureMipmap(m_RendererID);
	}
	else
	{
		std::cout << "Failed to load Texture: " << m_FilePath.c_str() << std::endl;
	}
	if (m_TexData) { stbi_image_free(m_TexData); }

}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture2D::Bind(unsigned int slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void Texture2D::UnBind() const
{

}

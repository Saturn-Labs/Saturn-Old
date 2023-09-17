#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

#include <glad/glad.h>

#include "stb_image.h"

namespace Saturn
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, bool retain_data)
		: m_Path(path), m_RetainData(retain_data)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;

		m_TextureData = stbi_load(path.c_str(), &width, &height, &channels, 0);

		m_Width = (UInt32)width;
		m_Height = (UInt32)height;
		m_Channels = (UInt32)channels;

		GLenum internalFormat = 0;
		GLenum format = 0;
		switch (channels)
		{
			case 3:
				internalFormat = GL_RGB8;
				format = GL_RGB;
				break;

			case 4:
				internalFormat = GL_RGBA8;
				format = GL_RGBA;
				break;
			default:
				internalFormat = GL_RGB8;
				format = GL_RGB;
				break;
		}

		ST_CORE_ASSERT(internalFormat, "Texture format not supported!");

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_TextureData);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!retain_data && m_TextureData)
			stbi_image_free(m_TextureData);
	}

	OpenGLTexture2D::OpenGLTexture2D(UInt32 width, UInt32 height, int channels)
		: m_Path("..."), m_Width(width), m_Height(height), m_Channels(channels), m_RetainData(true)
	{
		m_TextureData = new unsigned char[width * height * channels];
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_Id);
		if (m_TextureData && m_RetainData)
			stbi_image_free(m_TextureData);
	}

	glm::vec2 OpenGLTexture2D::GetSize() const
	{
		return glm::vec2(GetWidth(), GetHeight());
	}

	UInt32 OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	UInt32 OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	UInt32 OpenGLTexture2D::GetChannels() const
	{
		return m_Channels;
	}

	void OpenGLTexture2D::Bind(UInt32 slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	unsigned char* OpenGLTexture2D::GetNativeTextureData() const
	{
		return m_TextureData;
	}

	UInt32 OpenGLTexture2D::GetTextureNativeID() const
	{
		return m_Id;
	}

	void OpenGLTexture2D::EditSubImage(int x, int y, int width, int height, unsigned char* data)
	{
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}
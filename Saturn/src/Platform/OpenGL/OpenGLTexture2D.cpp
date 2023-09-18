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

		switch (channels)
		{
			case 3:
				m_InternalFormat = GL_RGB8;
				m_Format = GL_RGB;
				break;

			case 4:
				m_InternalFormat = GL_RGBA8;
				m_Format = GL_RGBA;
				break;
			default:
				m_InternalFormat = GL_RGB8;
				m_Format = GL_RGB;
				break;
		}

		ST_CORE_ASSERT(!(channels != 3 && channels != 4), "Texture format not supported!");

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, m_TextureData);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (!retain_data && m_TextureData)
			stbi_image_free(m_TextureData);
	}

	OpenGLTexture2D::OpenGLTexture2D(UInt32 width, UInt32 height, int channels)
		: m_Path("..."), m_Width(width), m_Height(height), m_Channels(channels), m_RetainData(true)
	{
		m_TextureData = new unsigned char[width * height * channels];

		switch (m_Channels)
		{
			case 3:
				m_InternalFormat = GL_RGB8;
				m_Format = GL_RGB;
				break;

			case 4:
				m_InternalFormat = GL_RGBA8;
				m_Format = GL_RGBA;
				break;
			default:
				m_InternalFormat = GL_RGB8;
				m_Format = GL_RGB;
				break;
		}

		ST_CORE_ASSERT(!(m_Channels != 3 && m_Channels != 4), "Texture format not supported!");

		glGenTextures(1, &m_Id);
		glBindTexture(GL_TEXTURE_2D, m_Id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, m_TextureData);
		glBindTexture(GL_TEXTURE_2D, 0);
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

	void OpenGLTexture2D::Unbind(UInt32 slot) const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::SetData(void* data, UInt32 size)
	{
		if (m_RetainData && m_TextureData)
		{
			delete m_TextureData;
		}

		m_TextureData = new unsigned char[size];
		m_TextureData = (Byte*)memcpy(m_TextureData, data, size);

		ST_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "[OpenGLTexture2D] UInt32 size is different from required texture buffer size!");
		
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, m_TextureData);
		Unbind();
	}

	unsigned char* OpenGLTexture2D::GetNativeTextureData() const
	{
		return m_TextureData;
	}

	UInt32 OpenGLTexture2D::GetTextureNativeID() const
	{
		return m_Id;
	}
}
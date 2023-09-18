#pragma once
#include "Saturn/Rendering/Texture2D.h"
#include <string>

namespace Saturn
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, bool retain_data = false);
		OpenGLTexture2D(UInt32 width, UInt32 height, int channels = 3);
		virtual ~OpenGLTexture2D();

		virtual glm::vec2 GetSize() const override final;
		virtual UInt32 GetWidth() const override final;
		virtual UInt32 GetHeight() const override final;
		virtual UInt32 GetChannels() const override final;

		virtual void Bind(UInt32 slot = 0) const override final;
		virtual void Unbind(UInt32 slot = 0) const override final;

		virtual void SetData(void* data, UInt32 size = 0) override final;

		virtual unsigned char* GetNativeTextureData() const override final;
		virtual UInt32 GetTextureNativeID() const override final;
	private:
		bool m_RetainData = false;

		std::string m_Path;
		
		UInt32 m_Width = 1;
		UInt32 m_Height = 1;
		UInt32 m_Channels = 0;

		Int32 m_Format = 0;
		Int32 m_InternalFormat = 0;
		
		UInt32 m_Id = 0;

		unsigned char* m_TextureData = nullptr;
	};
}
#pragma once
#include <glm/glm.hpp>

namespace Saturn
{
	class Texture
	{
	public:
		virtual ~Texture()
		{
		};

		virtual glm::vec2 GetSize() const = 0;
		virtual UInt32 GetWidth() const = 0;
		virtual UInt32 GetHeight() const = 0;
		virtual UInt32 GetChannels() const = 0;

		virtual void Bind(UInt32 slot = 0) const = 0;
		virtual void Unbind(UInt32 slot = 0) const = 0;

		virtual void SetData(void* data, UInt32 size = 0) = 0;

		virtual unsigned char* GetNativeTextureData() const = 0;
		virtual UInt32 GetTextureNativeID() const = 0;
	};
}
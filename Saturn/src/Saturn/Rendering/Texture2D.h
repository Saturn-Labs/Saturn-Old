#pragma once
#include "Saturn/Rendering/Texture.h"

namespace Saturn
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;
	public:
		static Ref<Texture2D> Create(const std::string& path, bool retain_data = false);
		static Ref<Texture2D> Create(UInt32 width, UInt32 height);
	};
}
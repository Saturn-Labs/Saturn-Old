#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/Renderer.h"

namespace Saturn
{
	Ref<Texture2D> Texture2D::Create(const std::string& path, bool retain_data)
	{
		switch (RendererAPI::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<OpenGLTexture2D>(new OpenGLTexture2D(path, retain_data));
				break;
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(UInt32 width, UInt32 height)
	{
		switch (RendererAPI::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<OpenGLTexture2D>(new OpenGLTexture2D(width, height));
				break;
		}
		return nullptr;
	}
}
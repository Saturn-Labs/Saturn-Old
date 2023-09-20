#include "SaturnPch.h"
#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Saturn/Rendering/Renderer.h"

namespace Saturn
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specs)
	{
		ST_PROFILE_FUNCTION();
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<Framebuffer>(new OpenGLFramebuffer(specs));
				break;
		}
		return nullptr;
	}
}
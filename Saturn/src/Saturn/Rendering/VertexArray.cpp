#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Saturn/Rendering/VertexArray.h"
#include "Saturn/Rendering/Renderer.h"

namespace Saturn
{
	Ref<VertexArray> VertexArray::Create()
	{
		ST_PROFILE_FUNCTION();
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::API::None:
				ST_CORE_ASSERT(false, "[Saturn rendering error] Render API none not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return Ref<OpenGLVertexArray>(new OpenGLVertexArray());
		}

		ST_CORE_ASSERT(false, "[Saturn rendering error] Invalid Render API!");
		return nullptr;
	}
}
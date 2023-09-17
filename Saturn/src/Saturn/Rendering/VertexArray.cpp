#include "saturnpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Saturn
{
	Ref<VertexArray> VertexArray::Create()
	{
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
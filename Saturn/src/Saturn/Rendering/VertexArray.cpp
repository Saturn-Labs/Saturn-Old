#include "saturnpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Saturn
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::None:
				ST_CORE_ASSERT(false, "[Saturn rendering error] Render API none not supported!");
				return nullptr;

			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}

		ST_CORE_ASSERT(false, "[Saturn rendering error] Invalid Render API!");
		return nullptr;
	}
}
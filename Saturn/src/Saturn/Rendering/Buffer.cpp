#include "saturnpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Saturn
{
	VertexBuffer* VertexBuffer::Create(float* vertices, UInt32 size)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
				break;
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(UInt32* indices, UInt32 size)
	{
		switch (Renderer::GetRendererAPI())
		{
			case RendererAPI::OpenGL:
				return new OpenGLIndexBuffer(indices, size);
				break;
		}
		return nullptr;
	}
}
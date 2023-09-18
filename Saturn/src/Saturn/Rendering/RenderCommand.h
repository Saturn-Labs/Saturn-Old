#pragma once
#include "Saturn/Rendering/RendererAPI.h"

namespace Saturn
{
	class RenderCommand
	{
	public:
		inline static void Initialize()
		{
			s_RendererAPI->Initialize();
		}

		inline static void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static float GetTime()
		{
			return s_RendererAPI->GetTime();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetDrawMode(DrawMode mode = DrawMode::Full)
		{
			s_RendererAPI->SetDrawMode(mode);
		}

		inline static void DrawIndexed(const VertexArray* vertexArray)
		{
			vertexArray->Bind();
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}
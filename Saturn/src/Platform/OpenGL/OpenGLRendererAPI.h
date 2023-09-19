#pragma once
#include "Saturn/Rendering/RendererAPI.h"

namespace Saturn
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Initialize() override final;
		virtual void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height) override final;
		virtual float GetTime() override final;
		virtual void SetClearColor(const glm::vec4& color) override final;
		virtual void Clear() override final;

		virtual void SetDrawMode(DrawMode mode) override final;

		virtual void DrawIndexed(const VertexArray* vertexArray) override final;
		virtual void DrawIndexed(const VertexArray* vertexArray, UInt32 count) override final;
	};
}
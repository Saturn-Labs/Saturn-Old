#pragma once
#include "Saturn/Rendering/RendererAPI.h"

namespace Saturn
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Initialize() override final;
		virtual void SetClearColor(const glm::vec4& color) override final;
		virtual void Clear() override final;

		virtual void DrawIndexed(const Saturn::Ref<VertexArray>& vertexArray) override final;
	};
}
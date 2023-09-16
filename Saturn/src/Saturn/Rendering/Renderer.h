#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Saturn
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetRendererAPI()
		{
			return RendererAPI::GetRendererAPI();
		}

	public:
	private:
		struct SceneData
		{
			glm::mat4 ViewProjection = glm::mat4(1.0f);
		};

		static SceneData* m_SceneData;
	};
}
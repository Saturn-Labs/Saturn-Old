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
		static void Initialize();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transformation = glm::mat4(1.0f));

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
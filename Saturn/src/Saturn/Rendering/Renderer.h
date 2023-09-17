#pragma once
#include "Saturn/Rendering/RendererAPI.h"
#include "Saturn/Rendering/RenderCommand.h"
#include "Saturn/Camera/OrthoCamera.h"
#include "Saturn/Shader/Shader.h"

namespace Saturn
{
	class Renderer
	{
	public:
		static void Initialize();
		static void OnWindowResize(UInt32 x, UInt32 y, UInt32 width, UInt32 height);
		static float GetTime();
		static void BeginScene(const OrthoCamera& camera);
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
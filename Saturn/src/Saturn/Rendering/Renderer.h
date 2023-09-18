#pragma once
#include "Saturn/Rendering/RendererAPI.h"
#include "Saturn/Rendering/RenderCommand.h"
#include "Saturn/Camera/OrthoCamera.h"
#include "Saturn/Shader/Shader.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/TransformationMatrix.h"

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
		static void Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transformation = glm::mat4(1.0f));
		static void Submit(Shader* shader, const VertexArray* vertexArray, const glm::mat4& transformation = glm::mat4(1.0f));

		static void DrawCube(const TransformationMatrix& matrix, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawCube(const TransformationMatrix& matrix, const Ref<Texture>& texture, const glm::vec4& color = glm::vec4(1.0f));

		inline static RendererAPI::API GetRendererAPI()
		{
			return RendererAPI::GetRendererAPI();
		}

	public:
		struct SceneData
		{
			glm::mat4 ViewProjection = glm::mat4(1.0f);
		};

		struct RenderData
		{
			Ref<Shader> DefaultShader;
			Ref<VertexArray> CubeVertexArray;
			Ref<Texture2D> DefaultTexture;
		};
	private:
		static Scoped<SceneData> s_SceneData;
		static Scoped<RenderData> s_RenderData;
		static bool s_InScene;
	};
}
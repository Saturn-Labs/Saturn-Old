#pragma once
#include "Saturn/Camera/OrthoCamera.h"

#include "VertexArray.h"
#include "Saturn/Shader/Shader.h"
#include "Saturn/Rendering/TransformationMatrix.h"
#include "Saturn/Rendering/Texture2D.h"

namespace Saturn
{
	class Renderer2D
	{
	public:
		struct Data
		{
			Ref<VertexArray> QuadVertexArray;
			Ref<Shader> SpritesDefaultShader;
			Ref<Texture2D> DefaultTexture;
			glm::mat4 ViewProjection;
		};

		static Data* s_Data;
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		#pragma region Primitives
		static void DrawQuad(const Saturn::TransformationMatrix& transform, const glm::vec4& color);
		static void DrawQuad(const Saturn::TransformationMatrix& transform, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		#pragma endregion
	};
}
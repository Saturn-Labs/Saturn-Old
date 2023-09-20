#pragma once
#include "Saturn/Camera/Camera.h"

#include "VertexArray.h"
#include "Saturn/Shader/Shader.h"
#include "Saturn/Rendering/TransformationMatrix.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Rendering/SubTexture2D.h"
#include "Saturn/Scene/Components/Transform.h"
#include "Saturn/Scene/Components/SpriteRenderer.h"
#include "Saturn/Scene/Components/Tag.h"
#include "TransformedCamera.h"

namespace Saturn
{
	class Renderer2D
	{
	public:
		struct QuadVertex
		{
			glm::vec3 VertexPosition;
			glm::vec4 Color;
			glm::vec2 TextureCoord;
			float TextureIndex;

			glm::vec3 ModelPosition;
			glm::vec3 ModelRotation;
			glm::vec3 ModelScale;
		};
		struct Data
		{
			static const UInt32 MaxQuadsPerBatch = 50000;
			static const UInt32 MaxVerticesPerBatch = MaxQuadsPerBatch * 4;
			static const UInt32 MaxIndicesPerBatch = MaxQuadsPerBatch * 6;
			static const UInt32 MaxTextureSlots = 32;

			const glm::vec4 QuadVertices[4]{
				{ -0.5f, -0.5f, 0.0f, 1.0f },
				{  0.5f, -0.5f, 0.0f, 1.0f },
				{  0.5f,  0.5f, 0.0f, 1.0f },
				{ -0.5f,  0.5f, 0.0f, 1.0f },
			};

			const glm::vec2 QuadTexCoords[4]{
				{ 0, 0 },
				{ 1, 0 },
				{ 1, 1 },
				{ 0, 1 },
			};

			const Int32 Samplers[32]{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
			};

			Ref<VertexArray> QuadVertexArray;
			Ref<VertexBuffer> QuadVertexBuffer;

			Ref<Shader> SpritesDefaultShader;
			Ref<Texture2D> DefaultTexture;
			glm::mat4 ViewProjection = glm::mat4(1.0f);

			UInt32 QuadIndexCount = 0;
			QuadVertex* QuadVertexBufferBase = nullptr;
			QuadVertex* QuadVertexBufferPointer = nullptr;

			std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
			UInt32 TextureSlotIndex = 1;
		};
		struct Statistics
		{
			UInt32 DrawCalls = 0;
			UInt32 QuadsCount = 0;

			UInt32 GetVertexCount()
			{
				return QuadsCount * 4;
			}

			UInt32 GetIndicesCount()
			{
				return QuadsCount * 6;
			}
		};
		static Statistics Stats;
		static Data* s_Data;
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const TransformedCamera& transformedCamera);
		static void EndScene();
		static void Flush();


		#pragma region DrawPrimitives
		static void DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<Texture2D>& texture, const glm::vec2 textureCoords[4], const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<SubTexture2D>& subTexture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const Component::Transform& transform, const Component::SpriteRenderer& renderer);
		#pragma endregion

		static void ResetStats()
		{
			Stats = {};
		}

		static Statistics& GetStats()
		{
			return Stats;
		}

	private:
		static void FlushAndReset();
	};
}
#include "SaturnPch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

namespace Saturn
{
	Renderer2D::Data* Renderer2D::s_Data = nullptr;
	Renderer2D::Statistics Renderer2D::Stats{};

	void Renderer2D::Initialize()
	{
		ST_PROFILE_FUNCTION();

		s_Data = new Renderer2D::Data();

		s_Data->QuadVertexArray = VertexArray::Create();

		{
			s_Data->QuadVertexBuffer = VertexBuffer::Create(s_Data->MaxVerticesPerBatch * sizeof(QuadVertex));
			s_Data->QuadVertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "VertexPosition" },
				{ ShaderDataType::Float4, "Color" },
				{ ShaderDataType::Float2, "TextureCoord" },
				{ ShaderDataType::Float, "TextureIndex" },
				{ ShaderDataType::Float3, "ModelPosition" },
				{ ShaderDataType::Float3, "ModelRotation" },
				{ ShaderDataType::Float3, "ModelScale" },
			});
			s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);
		}

		s_Data->QuadVertexBufferBase = new QuadVertex[s_Data->MaxVerticesPerBatch];

		UInt32* quadIndices = new UInt32[s_Data->MaxIndicesPerBatch];

		UInt32 offset = 0;
		for (UInt32 i = 0; i < s_Data->MaxIndicesPerBatch; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, s_Data->MaxIndicesPerBatch);
		s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] quadIndices;

		s_Data->SpritesDefaultShader = Shader::Create("resources/shaders/Sprites-Default.sshader");

		s_Data->DefaultTexture = Texture2D::Create(1, 1, 4);

		UInt32 pixelColor = 0xffffffff;
		s_Data->DefaultTexture->SetData(&pixelColor, 4);

		s_Data->TextureSlots[0] = s_Data->DefaultTexture;

		s_Data->SpritesDefaultShader->Bind();

		#pragma region TEMPORARY
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture0", 0);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture1", 1);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture2", 2);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture3", 3);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture4", 4);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture5", 5);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture6", 6);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture7", 7);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture8", 8);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture9", 9);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture10", 10);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture11", 11);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture12", 12);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture13", 13);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture14", 14);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture15", 15);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture16", 16);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture17", 17);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture18", 18);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture19", 19);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture20", 20);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture21", 21);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture22", 22);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture23", 23);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture24", 24);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture25", 25);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture26", 26);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture27", 27);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture28", 28);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture29", 29);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture30", 30);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSlots.Texture31", 31);
		#pragma endregion
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		s_Data->SpritesDefaultShader->Bind();
		s_Data->SpritesDefaultShader->UploadUniformMat4("Projection", camera.GetProjectionMatrix());
		s_Data->SpritesDefaultShader->UploadUniformFloat3("CameraPosition", camera.GetPosition());
		s_Data->SpritesDefaultShader->UploadUniformFloat("CameraRotation", camera.GetRotation());

		s_Data->QuadVertexBufferPointer = s_Data->QuadVertexBufferBase;
		s_Data->QuadIndexCount = 0;
		s_Data->TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		ST_PROFILE_FUNCTION();

		UInt32 dataSize = (Byte*)s_Data->QuadVertexBufferPointer - (Byte*)s_Data->QuadVertexBufferBase;
		s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (UInt32 i = 0; i < s_Data->TextureSlotIndex; i++)
		{
			s_Data->TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray.get(), s_Data->QuadIndexCount);
		Stats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data->QuadVertexBufferPointer = s_Data->QuadVertexBufferBase;
		s_Data->QuadIndexCount = 0;
		s_Data->TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();

		if (s_Data->QuadIndexCount >= Renderer2D::Data::MaxIndicesPerBatch)
			FlushAndReset();

		for (int i = 0; i < 4; i++)
		{
			s_Data->QuadVertexBufferPointer->VertexPosition = s_Data->QuadVertices[i];
			s_Data->QuadVertexBufferPointer->Color = color;
			s_Data->QuadVertexBufferPointer->TextureCoord = s_Data->QuadTexCoords[i];
			s_Data->QuadVertexBufferPointer->TextureIndex = 0.0f;
			s_Data->QuadVertexBufferPointer->ModelPosition = position;
			s_Data->QuadVertexBufferPointer->ModelRotation = rotation;
			s_Data->QuadVertexBufferPointer->ModelScale = scale;
			s_Data->QuadVertexBufferPointer++;
		}
		s_Data->QuadIndexCount += 6;

		Stats.QuadsCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();

		if (s_Data->QuadIndexCount >= Renderer2D::Data::MaxIndicesPerBatch)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (UInt32 i = 1; i < s_Data->TextureSlotIndex; i++)
		{
			if (*s_Data->TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data->TextureSlotIndex;
			s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
			s_Data->TextureSlotIndex++;
		}

		for (int i = 0; i < 4; i++)
		{
			s_Data->QuadVertexBufferPointer->VertexPosition = s_Data->QuadVertices[i];
			s_Data->QuadVertexBufferPointer->Color = color;
			s_Data->QuadVertexBufferPointer->TextureCoord = s_Data->QuadTexCoords[i];
			s_Data->QuadVertexBufferPointer->TextureIndex = textureIndex;
			s_Data->QuadVertexBufferPointer->ModelPosition = position;
			s_Data->QuadVertexBufferPointer->ModelRotation = rotation;
			s_Data->QuadVertexBufferPointer->ModelScale = scale;
			s_Data->QuadVertexBufferPointer++;
		}
		s_Data->QuadIndexCount += 6;

		Stats.QuadsCount++;
	}
}
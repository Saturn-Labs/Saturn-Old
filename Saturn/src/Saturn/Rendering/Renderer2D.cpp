#include "SaturnPch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

namespace Saturn
{
	Renderer2D::Data* Renderer2D::s_Data = nullptr;

	void Renderer2D::Initialize()
	{
		s_Data = new Renderer2D::Data();

		float vertices[5 * 4]{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		unsigned int indices[6]{
			0, 1, 2,
			2, 3, 0,
		};

		s_Data->QuadVertexArray = VertexArray::Create();
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "VertexPosition" },
			{ ShaderDataType::Float2, "TextureUV" }
		};
		
		vertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);
		s_Data->QuadVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, 6));

		s_Data->SpritesDefaultShader = Shader::Create("resources/shaders/Sprites-Default.sshader");

		s_Data->DefaultTexture = Texture2D::Create(1, 1, 4);

		UInt32 pixelColor = 0xffffffff;
		s_Data->DefaultTexture->SetData(&pixelColor, 4);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		s_Data->SpritesDefaultShader->Bind();
		s_Data->SpritesDefaultShader->UploadUniformMat4("ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const TransformationMatrix& transform, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();
		s_Data->DefaultTexture->Bind(0);
		s_Data->SpritesDefaultShader->Bind();
		s_Data->SpritesDefaultShader->UploadUniformFloat4("TintColor", color);
		s_Data->SpritesDefaultShader->UploadUniformMat4("ObjectTransformation", transform);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSample", 0);

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray.get());
	}

	void Renderer2D::DrawQuad(const Saturn::TransformationMatrix& transform, const Ref<Texture2D>& texture, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();
		texture->Bind(0);
		s_Data->SpritesDefaultShader->Bind();
		s_Data->SpritesDefaultShader->UploadUniformFloat4("TintColor", color);
		s_Data->SpritesDefaultShader->UploadUniformMat4("ObjectTransformation", transform);
		s_Data->SpritesDefaultShader->UploadUniformInt("TextureSample", 0);

		RenderCommand::DrawIndexed(s_Data->QuadVertexArray.get());
	}
}
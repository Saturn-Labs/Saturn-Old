#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Rendering/Renderer2D.h"

namespace Saturn
{
	Scoped<Renderer::SceneData> Renderer::s_SceneData = Scoped<Renderer::SceneData>(new Renderer::SceneData());
	Scoped<Renderer::RenderData> Renderer::s_RenderData = Scoped<Renderer::RenderData>(new Renderer::RenderData());

	bool Renderer::s_InScene = false;

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();

		float vertices[5 * 24]{
			 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

			-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
			-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
			0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
			0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
			0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
			0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
			-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
			0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
			-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
			0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
		};
		unsigned int indices[3 * 12]{
			// front and back
			   0, 3, 2,
			   2, 1, 0,
			   4, 5, 6,
			   6, 7 ,4,
			   // left and right
			   11, 8, 9,
			   9, 10, 11,
			   12, 13, 14,
			   14, 15, 12,
			   // bottom and top
			   16, 17, 18,
			   18, 19, 16,
			   20, 21, 22,
			   22, 23, 20
		};

		s_RenderData->CubeVertexArray = VertexArray::Create();
		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "VertexPosition" },
			{ ShaderDataType::Float2, "TextureUV" }
		};

		vertexBuffer->SetLayout(layout);
		s_RenderData->CubeVertexArray->AddVertexBuffer(vertexBuffer);
		s_RenderData->CubeVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, 3 * 12));

		s_RenderData->DefaultShader = Shader::Create("resources/shaders/Sprites-Default.sshader");

		s_RenderData->DefaultTexture = Texture2D::Create(1, 1, 4);

		UInt32 pixelColor = 0xffffffff;
		s_RenderData->DefaultTexture->SetData(&pixelColor, 4);

		Renderer2D::Initialize();
	}

	void Renderer::OnWindowResize(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}

	float Renderer::GetTime()
	{
		return RenderCommand::GetTime();
	}

	void Renderer::BeginScene(const OrthoCamera& camera)
	{
		s_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
		s_RenderData->DefaultShader->UploadUniformMat4("ViewProjectionMatrix", s_SceneData->ViewProjection);
		s_InScene = true;
	}

	void Renderer::EndScene()
	{
		s_InScene = false;
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transformation)
	{
		Renderer::Submit(shader.get(), vertexArray.get(), transformation);
	}

	void Renderer::Submit(Shader& shader, const VertexArray& vertexArray, const glm::mat4& transformation)
	{
		Renderer::Submit(&shader, &vertexArray, transformation);
	}

	void Renderer::Submit(Shader* shader, const VertexArray* vertexArray, const glm::mat4& transformation)
	{
		if (!shader && !vertexArray)
			ST_CORE_ASSERT(false, "[Saturn renderer submit] Shader or VertexArray is nullptr!");

		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjection);
		shader->UploadUniformMat4("u_Transformation", transformation);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::DrawCube(const TransformationMatrix& matrix, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();
		s_RenderData->DefaultTexture->Bind(0);
		s_RenderData->DefaultShader->Bind();
		s_RenderData->DefaultShader->UploadUniformFloat4("TintColor", color);
		s_RenderData->DefaultShader->UploadUniformMat4("ObjectTransformation", matrix);
		s_RenderData->DefaultShader->UploadUniformInt("TextureSample", 0);

		RenderCommand::DrawIndexed(s_RenderData->CubeVertexArray.get());
	}

	void Renderer::DrawCube(const TransformationMatrix& matrix, const Ref<Texture>& texture, const glm::vec4& color)
	{
		ST_PROFILE_FUNCTION();
		texture->Bind(0);
		s_RenderData->DefaultShader->Bind();
		s_RenderData->DefaultShader->UploadUniformFloat4("TintColor", color);
		s_RenderData->DefaultShader->UploadUniformMat4("ObjectTransformation", matrix);
		s_RenderData->DefaultShader->UploadUniformInt("TextureSample", 0);

		RenderCommand::DrawIndexed(s_RenderData->CubeVertexArray.get());
	}
}
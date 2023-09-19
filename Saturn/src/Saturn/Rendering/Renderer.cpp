#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Rendering/Renderer2D.h"
#include <glad/glad.h>
#include "Saturn/Rendering/Helper.h"

namespace Saturn
{
	Scoped<Renderer::SceneData> Renderer::s_SceneData = Scoped<Renderer::SceneData>(new Renderer::SceneData());
	Scoped<Renderer::RenderData> Renderer::s_RenderData = Scoped<Renderer::RenderData>(new Renderer::RenderData());

	bool Renderer::s_InScene = false;

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();

		glm::vec3 vertices[8]{
			{  0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f,  0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },

			{  0.5f, -0.5f,  0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{  0.5f,  0.5f,  0.5f },
		};

		glm::vec3 normals[8] = {
			Helper::CalculateNormal(vertices[0], vertices[1], vertices[2]),
			Helper::CalculateNormal(vertices[0], vertices[1], vertices[2]),
			Helper::CalculateNormal(vertices[2], vertices[3], vertices[0]),
			Helper::CalculateNormal(vertices[2], vertices[3], vertices[0]),
		};

		glm::vec2 texCoords[8]{
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },

			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
		};

		unsigned int indices[12]{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
		};

		s_RenderData->CubeVertexArray = VertexArray::Create();

		//vertices
		{
			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create((float*)vertices, sizeof(vertices));
			BufferLayout layout = {
				{ ShaderDataType::Float3, "VertexPosition" }
			};

			vertexBuffer->SetLayout(layout);
			s_RenderData->CubeVertexArray->AddVertexBuffer(vertexBuffer);
		}

		//texcoords
		{
			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create((float*)texCoords, sizeof(texCoords));
			BufferLayout layout = {
				{ ShaderDataType::Float2, "TextureUV" }
			};

			vertexBuffer->SetLayout(layout);
			s_RenderData->CubeVertexArray->AddVertexBuffer(vertexBuffer);
		}

		//normals
		{
			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create((float*)normals, sizeof(normals));
			BufferLayout layout = {
				{ ShaderDataType::Float3, "Normal" }
			};

			vertexBuffer->SetLayout(layout);
			s_RenderData->CubeVertexArray->AddVertexBuffer(vertexBuffer);
		}

		s_RenderData->CubeVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(UInt32)));

		s_RenderData->DefaultShader = Shader::Create("resources/shaders/FlatColor-Default.sshader");

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

	void Renderer::BeginScene(const OrthoCamera& camera, const LightParams& params)
	{
		s_SceneData->Projection = camera.GetProjectionMatrix();
		s_RenderData->DefaultShader->UploadUniformMat4("ViewProjectionMatrix", s_SceneData->Projection);
		s_RenderData->DefaultShader->UploadUniformFloat3("LightPosition", params.LightPosition);
		s_RenderData->DefaultShader->UploadUniformFloat4("LightColor", params.LightColor);
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
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->Projection);
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
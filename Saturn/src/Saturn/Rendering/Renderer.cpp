#include "SaturnPch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Rendering/Renderer2D.h"

namespace Saturn
{
	Scoped<Renderer::SceneData> Renderer::s_SceneData = Scoped<Renderer::SceneData>(new Renderer::SceneData());
	bool Renderer::s_InScene = false;

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();
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
}
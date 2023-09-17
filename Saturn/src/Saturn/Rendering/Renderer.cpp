#include "saturnpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Saturn
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData();

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transformation)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjection);
		shader->UploadUniformMat4("u_Transformation", transformation);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
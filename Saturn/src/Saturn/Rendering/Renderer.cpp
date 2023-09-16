#include "saturnpch.h"
#include "Renderer.h"

namespace Saturn
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjection = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();
		shader->SetUniformMat4("u_ViewProjection", m_SceneData->ViewProjection);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
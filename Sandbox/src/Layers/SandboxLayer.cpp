#include "SandboxLayer.h"

#include "Saturn/Rendering/RenderCommand.h"
#include "Saturn/Shader/ShaderPreprocessor.h"
#include "Saturn/Events/EventType.h"
#include "Saturn/Core/Application.h"

#include "imgui.h"

SandboxLayer::SandboxLayer()
	: Saturn::Layer("SandboxLayer"), m_CameraController(1280.0f / 720.0f, true)
{
	Saturn::Application::Get().GetWindow().SetVSync(false);

	m_ShaderLibrary.Load("resources/shaders/textures-default.sshader");
	m_ShaderLibrary.Load("resources/shaders/circle.sshader");

	m_VertexArray = Saturn::VertexArray::Create();
	float vertices[5 * 4]{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	m_VertexBuffer = Saturn::VertexBuffer::Create(vertices, sizeof(vertices));
	Saturn::BufferLayout layout = {
		{ Saturn::ShaderDataType::Float3, "a_Position" },
		{ Saturn::ShaderDataType::Float2, "a_TexCoord" }
	};
	m_VertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	unsigned int indices[6]{
		0, 1, 2,
		2, 3, 0,
	};
	m_IndexBuffer = Saturn::IndexBuffer::Create(indices, 6);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_Texture = Saturn::Texture2D::Create("resources/images/box.png", true);
	m_Texture->Bind();

	auto& texDefaultShader = *m_ShaderLibrary.Get("textures-default");

	texDefaultShader.Bind();
	texDefaultShader.UploadUniformInt("u_Texture", 0);
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(Saturn::Time time)
{
	m_CameraController.OnUpdate(time);

	Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Saturn::RenderCommand::Clear();

	Saturn::Renderer::BeginScene(m_CameraController.GetCamera(), {});

	static auto& texDefaultShader = m_ShaderLibrary.Get("textures-default");
	texDefaultShader->UploadUniformFloat4("u_Color", m_Color);

	//static auto& circleShader = m_ShaderLibrary.Get("circle");
	//circleShader->UploadUniformFloat4("u_Color", m_Color);

	Saturn::Renderer::Submit(texDefaultShader, m_VertexArray, Saturn::TransformationMatrix{ m_Position, m_Rotation, m_Scale });
	Saturn::Renderer::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
	if (ImGui::Begin("Control Properties"))
	{
		ImGui::SliderFloat3("Position", &m_Position[0], -500, 500);
		ImGui::SliderFloat3("Rotation", &m_Rotation[0], -180, 180);
		ImGui::SliderFloat3("Scale", &m_Scale[0], -300, 300);
		ImGui::ColorEdit4("Color", &m_Color[0]);
		ImGui::End();
	}

	ImGui::ShowMetricsWindow();
}

void SandboxLayer::OnEvent(Saturn::Event& event)
{
	m_CameraController.OnEvent(event);
}
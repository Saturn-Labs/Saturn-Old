#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
	: Saturn::Layer("SandboxLayer"),
	  m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	m_BasicShader = std::shared_ptr<Saturn::Shader>(new Saturn::Shader("resources/shaders/basic.vert", "resources/shaders/basic.frag"));
	m_VertexArray = std::shared_ptr<Saturn::VertexArray>(Saturn::VertexArray::Create());
	float vertices[3 * 4]{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	m_VertexBuffer = std::shared_ptr<Saturn::VertexBuffer>(Saturn::VertexBuffer::Create(vertices, sizeof(vertices)));
	Saturn::BufferLayout layout = {
		{ Saturn::ShaderDataType::Float3, "a_Position" }
	};
	m_VertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	unsigned int indices[6]{
		0, 1, 2,
		2, 3, 0,
	};
	m_IndexBuffer = std::shared_ptr<Saturn::IndexBuffer>(Saturn::IndexBuffer::Create(indices, 6));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
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

void SandboxLayer::OnUpdate()
{
	if (xdeg >= 180)
		xdegInc = -0.03f;
	else if (xdeg <= -180)
		xdegInc = 0.03f;

	if (ydeg >= 180)
		ydegInc = -0.07f;
	else if (ydeg <= -180)
		ydegInc = 0.07f;

	if (rotZ <= -180.0f)
		rotZInc = 0.95f;
	else if (rotZ >= 180.0f)
		rotZInc = -0.95f;

	xdeg += xdegInc;
	ydeg += ydegInc;
	rotZ += rotZInc;

	x = sinf(xdeg);
	y = sinf(ydeg);

	m_Camera.SetPosition({ x, y, 0 });
	m_Camera.SetRotation(rotZ);
	Saturn::Renderer::BeginScene(m_Camera);
	Saturn::Renderer::Submit(m_BasicShader, m_VertexArray);
	Saturn::Renderer::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(Saturn::Event& event)
{
}
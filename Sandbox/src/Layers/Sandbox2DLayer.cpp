#include "Sandbox2DLayer.h"

namespace Sandbox
{
	Sandbox2DLayer::Sandbox2DLayer() 
		: Layer("Sandbox2D"), m_OrthoCameraController(1280.0f / 720.0f, true)
	{
	}

	Sandbox2DLayer::~Sandbox2DLayer()
	{
	}

	void Sandbox2DLayer::OnAttach()
	{
		Saturn::Application::Get().GetWindow().SetVSync(false);

		m_Texture = Saturn::Texture2D::Create("resources/images/checkerpattern.png");

		m_ImGuiIO = &ImGui::GetIO();
		m_Attached = true;
	}

	void Sandbox2DLayer::OnDetach()
	{
		m_Attached = false;
	}

	void Sandbox2DLayer::OnUpdate(Saturn::Time time)
	{
		ST_PROFILE_FUNCTION();
		m_OrthoCameraController.OnUpdate(time);
		Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Saturn::RenderCommand::Clear();

		if (sinVal > 180)
			sinIncVal = -5.0f;
		else if (sinVal < -180)
			sinIncVal = 5.0f;
		sinVal += sinIncVal * time;

		sinValRes = sinf(sinVal);

		if (m_Attached)
		{
			Saturn::Renderer2D::ResetStats();
			Saturn::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
			
			Saturn::Renderer2D::DrawQuad(glm::vec3(m_Position.x + (sinValRes * 2.0f), m_Position.y + (sinValRes * 2.0f), 0.0f), m_RadianRotation, m_Scale, m_Texture, m_Color);

			for (float x = -7.0f; x < 7.0f; x += 0.5f)
			{
				for (float y = -7.0f; y < 7.0f; y += 0.5f)
				{
					Saturn::Renderer2D::DrawQuad(glm::vec3{ x, y, 0.0f } + m_Position, m_RadianRotation, glm::vec3(0.45f), glm::vec4{ (x + 7.0f) / 7.0f, 0.2f, (y + 7.0f) / 7.0f, 0.55f } * m_Color);
				}
			}

			Saturn::Renderer2D::EndScene();
		}
	}

	void Sandbox2DLayer::OnImGuiRender()
	{
		ST_PROFILE_FUNCTION();

		if (m_Attached && m_ShowUILayer && m_ImGuiIO)
		{
			ImGui::Begin("Sandbox2DLayer properties", &m_ShowUILayer);
			if (ImGui::BeginMenu("Metrics"))
			{
				ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_ImGuiIO->Framerate, m_ImGuiIO->Framerate);
				ImGui::Text("%d vertices, %d indices (%d triangles)", m_ImGuiIO->MetricsRenderVertices, m_ImGuiIO->MetricsRenderIndices, m_ImGuiIO->MetricsRenderIndices / 3);
				ImGui::Text("%d visible windows, %d active allocations", m_ImGuiIO->MetricsRenderWindows, m_ImGuiIO->MetricsActiveAllocations);
				ImGui::EndMenu();
			}
			ImGui::Spacing();
			ImGui::ColorEdit4("Quad Tint Color", &m_Color[0]);

			if (ImGui::TreeNode("Position"))
			{
				ImGui::SliderFloat("X", &m_Position[0], -2.0f, 2.0f);
				ImGui::SliderFloat("Y", &m_Position[1], -2.0f, 2.0f);
				ImGui::SliderFloat("Z", &m_Position[2], -2.0f, 2.0f);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rotation"))
			{
				ImGui::SliderAngle("X", &m_RadianRotation.x, -180.0f, 180.0f);
				ImGui::SliderAngle("Y", &m_RadianRotation.y, -180.0f, 180.0f);
				ImGui::SliderAngle("Z", &m_RadianRotation.z, -180.0f, 180.0f);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Scale"))
			{
				ImGui::DragFloat("X", &m_Scale[0], 1.0f, -3.0f, 3.0f);
				ImGui::DragFloat("Y", &m_Scale[1], 1.0f, -3.0f, 3.0f);
				ImGui::DragFloat("Z", &m_Scale[2], 1.0f, -3.0f, 3.0f);
				ImGui::TreePop();
			}

			ImGui::End();
		}

		if (Saturn::Input::GetKeyDown(Saturn::KeyCode::Insert))
			m_ShowUILayer = !m_ShowUILayer;
	}

	void Sandbox2DLayer::OnEvent(Saturn::Event& event)
	{
		m_OrthoCameraController.OnEvent(event);
	}
}



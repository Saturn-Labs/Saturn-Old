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

		{
			ST_PROFILE_SCOPE("RENDER CLEAR SCREEN AND CAMERA MATRIX");
			m_OrthoCameraController.OnUpdate(time);

			Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Saturn::RenderCommand::Clear();
		}

		if (m_Attached)
		{
			//m_ColorShader->Bind();
			//m_ColorShader->UploadUniformFloat4("u_TintColor", m_TintColor);
			//m_GradientShader->UploadUniformFloat("u_Time", Saturn::Renderer::GetTime());
			//m_GradientShader->UploadUniformFloat2("u_Resolution", { Saturn::Application::Get().GetWindow().GetWidth(), Saturn::Application::Get().GetWindow().GetHeight() });
			{
				ST_PROFILE_SCOPE("BeginScene");
				Saturn::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
			}
			{
				ST_PROFILE_SCOPE("DrawCall");
				Saturn::Renderer2D::DrawQuad(Saturn::TransformationMatrix{ m_Position, m_RadianRotation, m_Scale }, m_Texture, m_Color);
			}
			{
				ST_PROFILE_SCOPE("EndScene");
				Saturn::Renderer2D::EndScene();
			}


			//Saturn::Renderer::BeginScene(m_OrthoCameraController.GetCamera());
			//Saturn::Renderer::DrawCube(Saturn::TransformationMatrix{ m_Position, m_RadianRotation, m_Scale }, m_Texture, m_Color);
			//Saturn::Renderer::EndScene();
		}
	}

	void Sandbox2DLayer::OnImGuiRender()
	{
		ST_PROFILE_FUNCTION();

		if (m_Attached && m_ShowImGuiLayer && m_ImGuiIO)
		{
			ImGui::Begin("Sandbox2DLayer properties", &m_ShowImGuiLayer);
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
			m_ShowImGuiLayer = !m_ShowImGuiLayer;
	}

	void Sandbox2DLayer::OnEvent(Saturn::Event& event)
	{
		m_OrthoCameraController.OnEvent(event);
	}
}



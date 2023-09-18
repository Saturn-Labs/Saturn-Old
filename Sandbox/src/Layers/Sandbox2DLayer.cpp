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
		m_OrthoCameraController.OnUpdate(time);

		Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Saturn::RenderCommand::Clear();

		if (m_Attached)
		{
			//m_ColorShader->Bind();
			//m_ColorShader->UploadUniformFloat4("u_TintColor", m_TintColor);
			//m_GradientShader->UploadUniformFloat("u_Time", Saturn::Renderer::GetTime());
			//m_GradientShader->UploadUniformFloat2("u_Resolution", { Saturn::Application::Get().GetWindow().GetWidth(), Saturn::Application::Get().GetWindow().GetHeight() });

			Saturn::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());

			Saturn::Renderer2D::DrawQuad({ m_Position, m_RadianRotation / 3.14159265f * 180.0f, m_Scale }, m_Color);

			//Saturn::Renderer::Submit(m_ColorShader, m_VertexArray.get(), m_Transform.GetTransformationMatrix());
			/*for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					Saturn::Renderer2D::DrawQuad({ glm::vec3(m_Position.x + x, m_Position.y + y, 0), m_RadianRotation / 3.14159265f * 180.0f, glm::vec3(1.0f)}, m_Texture, glm::vec4(m_Color.r * ((float)x / 10.0f), m_Color.g * ((float)y / 10.0f), m_Color.b, m_Color.a));
				}
			}*/

			Saturn::Renderer2D::EndScene();
		}
	}

	void Sandbox2DLayer::OnImGuiRender()
	{
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



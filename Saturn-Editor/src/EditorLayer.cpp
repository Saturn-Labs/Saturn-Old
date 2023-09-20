#include "EditorLayer.h"

namespace Saturn
{
	EditorLayer::EditorLayer() 
		: Layer("EditorLayer")
	{
	}
	
	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		Application::Get().GetWindow().SetVSync(false);

		FramebufferSpecification frameBufferSpec{};
		frameBufferSpec.Width = 1280;
		frameBufferSpec.Height = 720;

		m_Framebuffer = Framebuffer::Create(frameBufferSpec);

		m_Texture = Texture2D::Create("resources/images/spritesheet_tiles.png");

		m_ActiveScene = CreateRef<Scene>();

		m_SquareEntity = m_ActiveScene->CreateEntity("Square Entity");
		m_SquareEntity.AddComponent<Component::SpriteRenderer>(Color(0.3f, 0.6f, 0.4f, 1.0f));

		//float ratio = 1280.0f / 720.0f;

		m_CameraEntity = m_ActiveScene->CreateEntity("Main Camera");
		Component::CameraComponent& cameraComponent = m_CameraEntity.AddComponent<Component::CameraComponent>();
		cameraComponent.Camera.SetOrthoSize(5);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Time time)
	{
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecs();
			m_SceneViewportSize.x > 0.0f && m_SceneViewportSize.y > 0.0f &&
			(spec.Width != m_SceneViewportSize.x || spec.Height != m_SceneViewportSize.y))
		{
			//m_Framebuffer->Resize((UInt32)m_SceneViewportSize.x, (UInt32)m_SceneViewportSize.y);

			
		}

		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		Renderer2D::ResetStats();
		
		//Scene Update/Draw/Render
		m_ActiveScene->OnUpdate(time);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		ST_PROFILE_FUNCTION();

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Dockspace", nullptr, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Editor"))
			{
				if (ImGui::MenuItem("Exit", NULL, false))
					Application::Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		if (m_ShowImGuiLayer)
		{
			Component::Transform& transform = m_SquareEntity.GetTransform();
			Component::SpriteRenderer& spriteRenderer = m_SquareEntity.GetComponent<Component::SpriteRenderer>();
			Component::Tag& tag = m_SquareEntity.GetTag();

			ImGui::Begin("EditorLayer properties", &m_ShowImGuiLayer);
			if (ImGui::BeginMenu("Metrics"))
			{
				ImGui::Text("Dear ImGui %s", ImGui::GetVersion());
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
				ImGui::Text("%d visible windows, %d active allocations", io.MetricsRenderWindows, io.MetricsActiveAllocations);
				ImGui::EndMenu();
			}
			ImGui::Spacing();
			ImGui::Text("%s", tag.Name.c_str());
			ImGui::ColorEdit4("My Entt Tint Color", &spriteRenderer.Color[0]);
			if (ImGui::TreeNode("Position"))
			{
				ImGui::SliderFloat("X", &transform.Position[0], -2.0f, 2.0f);
				ImGui::SliderFloat("Y", &transform.Position[1], -2.0f, 2.0f);
				ImGui::SliderFloat("Z", &transform.Position[2], -2.0f, 2.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Rotation"))
			{
				ImGui::SliderAngle("X", &transform.Rotation.x, -180.0f, 180.0f);
				ImGui::SliderAngle("Y", &transform.Rotation.y, -180.0f, 180.0f);
				ImGui::SliderAngle("Z", &transform.Rotation.z, -180.0f, 180.0f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Scale"))
			{
				ImGui::DragFloat("X", &transform.Scale[0], 1.0f, -3.0f, 3.0f);
				ImGui::DragFloat("Y", &transform.Scale[1], 1.0f, -3.0f, 3.0f);
				ImGui::DragFloat("Z", &transform.Scale[2], 1.0f, -3.0f, 3.0f);
				ImGui::TreePop();
			}

			//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::Begin("Viewport");

			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();

			Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);

			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			if (m_SceneViewportSize != *(glm::vec2*)&viewportSize)
			{
				m_SceneViewportSize = *(glm::vec2*)&viewportSize;
				m_Framebuffer->Resize((UInt32)m_SceneViewportSize.x, (UInt32)m_SceneViewportSize.y);
				m_ActiveScene->OnViewportResize((UInt32)m_SceneViewportSize.x, (UInt32)m_SceneViewportSize.y);
			}

			ImGui::Image((void*)m_Framebuffer->GetColorAttachmentID(), ImVec2(m_SceneViewportSize.x, m_SceneViewportSize.y), ImVec2{ 0,1 }, ImVec2{ 1,0 });
			ImGui::End();
			//ImGui::PopStyleVar();

			ImGui::End();
		}

		if (Input::GetKeyDown(KeyCode::Insert))
			m_ShowImGuiLayer = !m_ShowImGuiLayer;

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		
	}
}



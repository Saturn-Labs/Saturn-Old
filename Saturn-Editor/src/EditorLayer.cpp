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

		ScriptableBehaviour& cameraBehaviour = m_CameraEntity.AddScript<CameraBehaviour>();

		m_SceneHierarchy = CreateRef<SceneHierarchyPanel>(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Time time)
	{
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
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowMinSize.x = 370.0f;
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

		if (m_ShowUILayer)
		{
			
			m_SceneHierarchy->OnImGuiRender();

			ImGui::Begin("Viewport", NULL);

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
		}

		if (Input::GetKeyDown(KeyCode::Insert))
			m_ShowUILayer = !m_ShowUILayer;

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		
	}
}



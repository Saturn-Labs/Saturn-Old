#include "EditorLayer.h"
#include "Saturn/Serialization/SceneSerializer.h"

#include "Saturn/Common/PlatformUtils.h"
#include <glm/gtc/type_ptr.hpp>

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
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					EditorLayer::NewScene();
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					EditorLayer::OpenScene();
				}

				if (ImGui::MenuItem("Save As..", "Ctrl+Shift+S"))
				{
					EditorLayer::SaveAsScene();
				}

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

			// Gizmos
			Entity selectedEntity = m_SceneHierarchy->GetSelectedEntity();
			if (selectedEntity && m_GizmoType != -1)
			{
				ImGuizmo::SetOrthographic(false);

				ImGuizmo::SetDrawlist();
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
			
				//camera
				auto cameraEntity = m_ActiveScene->GetMainCamera();

				const auto& transform = cameraEntity.GetComponent<Component::Transform>();
				auto& entityTransform = selectedEntity.GetComponent<Component::Transform>();
				const auto& camera = cameraEntity.GetComponent<Component::CameraComponent>().Camera;

				const Matrix4x4& CameraProjection = camera.GetProjection();
				const Matrix4x4& CameraView = transform.GetInverseMatrix();
				Matrix4x4 GizmoModelMatrix = entityTransform.GetMatrix();

				ImGuizmo::Manipulate(glm::value_ptr(CameraView), glm::value_ptr(CameraProjection),
					(ImGuizmo::OPERATION)m_GizmoType,
					ImGuizmo::LOCAL, glm::value_ptr(GizmoModelMatrix));

				if (ImGuizmo::IsUsing())
				{
					entityTransform.SetMatrix(GizmoModelMatrix);
				}
			}

			ImGui::End();
		}

		if (Input::GetKeyDown(KeyCode::Insert))
			m_ShowUILayer = !m_ShowUILayer;

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(ST_BIND_EVENTFN(&EditorLayer::OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetRepeatCount() > 0)
			return false;

		bool isControlDown = Input::GetKeyCurrentState(KeyCode::LeftCtrl) == InputState::Down ||
			Input::GetKeyCurrentState(KeyCode::RightCtrl) == InputState::Down;

		bool isShiftDown = Input::GetKeyCurrentState(KeyCode::RightShift) == InputState::Down ||
			Input::GetKeyCurrentState(KeyCode::LeftShift) == InputState::Down;

		switch (e.GetKeyCode())
		{
			case KeyCode::Q:
				m_GizmoType = ImGuizmo::TRANSLATE;
				return true;
			case KeyCode::E:
				m_GizmoType = ImGuizmo::ROTATE;
				return true;
			case KeyCode::R:
				m_GizmoType = ImGuizmo::SCALE;
				return true;

			case KeyCode::N:
			{
				if (isControlDown)
					EditorLayer::NewScene();
				return true;
			}

			case KeyCode::O:
			{
				if (isControlDown)
					EditorLayer::OpenScene();
				return true;
			}

			case KeyCode::S:
			{
				if (isControlDown && isShiftDown)
					EditorLayer::SaveAsScene();
				return true;
			}
			default:
				return false;
		}
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((UInt32)m_SceneViewportSize.x, (UInt32)m_SceneViewportSize.y);
		m_SceneHierarchy->SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialog::OpenFile("Saturn Scene (*.saturn)\0*.saturn\0");
		if (!filepath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((UInt32)m_SceneViewportSize.x, (UInt32)m_SceneViewportSize.y);
			m_SceneHierarchy->SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(filepath);
		}
	}

	void EditorLayer::SaveAsScene()
	{
		std::string filepath = FileDialog::SaveFile("Saturn Scene (*.saturn)\0*.saturn\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}
}



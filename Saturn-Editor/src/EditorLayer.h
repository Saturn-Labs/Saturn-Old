#pragma once
#include "Saturn.h"
#include "Panels/SceneHierarchy.h"

#include "ImGuizmo/ImGuizmo.h"

namespace Saturn
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Time time) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
		virtual bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveAsScene();
	private:
		int m_GizmoType = -1;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_RadianRotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec4 m_Color = glm::vec4(1.0f);

		Ref<Texture2D> m_Texture;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		Entity m_SquareEntity;
		Entity m_CameraEntity;

		bool m_ShowUILayer = true;

		glm::vec2 m_SceneViewportSize = glm::vec2();

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		#pragma region Panels
		Ref<SceneHierarchyPanel> m_SceneHierarchy;
		#pragma endregion
	};
}
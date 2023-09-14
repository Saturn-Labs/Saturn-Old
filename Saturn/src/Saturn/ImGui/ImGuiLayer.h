#pragma once
#include "Saturn/Layer.h"
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/KeyCode.h"

enum ImGuiKey;
namespace Saturn
{
	enum class MouseButton;
	enum class KeyCode;

	class SATURNAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;
	private:
		inline static ImGuiKey GetImGuiKeyForKeyCode(Saturn::KeyCode keycode);
		inline static ImGuiKey GetImGuiModForKeyCode(Saturn::KeyCode keycode);

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0;
	};
}
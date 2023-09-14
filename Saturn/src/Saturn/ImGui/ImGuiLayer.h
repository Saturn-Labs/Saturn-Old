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

		virtual void OnAttach() override final;
		virtual void OnDetach() override final;
		virtual void OnImGuiRender() override final;

		void Begin();
		void End();
	private:
		inline static ImGuiKey GetImGuiKeyForKeyCode(Saturn::KeyCode keycode);
		inline static ImGuiKey GetImGuiModForKeyCode(Saturn::KeyCode keycode);
	private:
		float m_Time = 0;
	};
}
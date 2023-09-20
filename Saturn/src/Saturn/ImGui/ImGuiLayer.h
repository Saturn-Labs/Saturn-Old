#pragma once
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Input/KeyCode.h"
#include "Saturn/Main/Layer.h"
#include "Saturn/Rendering/RenderCommand.h"

enum ImGuiKey;
namespace Saturn
{
	enum class MouseButton;
	enum class KeyCode;

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override final;
		virtual void OnDetach() override final;
		virtual void OnImGuiRender() override final;
		virtual void OnEvent(Event& e) override final;

		void Begin();
		void End();

		void SetBlockEvents(bool value)
		{
			m_BlockEvents = value;
		}

		bool GetBlockEvents() const
		{
			return m_BlockEvents;
		}
	private:
		inline static ImGuiKey GetImGuiKeyForKeyCode(Saturn::KeyCode keycode);
		inline static ImGuiKey GetImGuiModForKeyCode(Saturn::KeyCode keycode);
	private:
		float m_Time = 0;
		bool m_IsOpen = false;
		bool m_BlockEvents = true;
		DrawMode m_CurrentDrawMode = DrawMode::Full;
	};
}
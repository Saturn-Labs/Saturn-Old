#pragma once
#include "Saturn/Window.h"
#include "GLFW/glfw3.h"

namespace Saturn
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override
		{
			return m_Data.Width;
		}

		inline virtual unsigned int GetHeight() const override
		{
			return m_Data.Height;
		}

		//Windows Window attribs 
		inline virtual void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
	private:
		virtual void Initialize(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
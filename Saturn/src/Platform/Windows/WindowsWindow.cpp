#include "saturnpch.h"
#include "WindowsWindow.h"
#include "Saturn/Core.h"
#include "Saturn/Log.h"

namespace Saturn
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Initialize(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Initialize(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ST_CORE_INFO("Creating new window on Windows Platform, \"{0}\" - ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: Terminate GLFW on shutdown
			int success = glfwInit();
			ST_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		if (s_GLFWInitialized && m_Window)
			glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
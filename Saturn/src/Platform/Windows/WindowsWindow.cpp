#include "SaturnPch.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Saturn/Input/Input.h"
#include "Saturn/Core/Core.h"
#include "Saturn/Core/Time.h"
#include "Saturn/IO/Log.h"

#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace Saturn
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int errorCode, const char* description)
	{
		ST_CORE_CRITICAL("Critical Error on GLFW: (0x{0:x}) - \"{1}\"", errorCode, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		ST_PROFILE_FUNCTION();

		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		ST_PROFILE_FUNCTION();

		Initialize(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ST_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Initialize(const WindowProps& props)
	{
		ST_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;


		ST_CORE_TRACE("Creating new window on Windows Platform, \"{0}\" - ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: Terminate GLFW on shutdown
			int success = glfwInit();
			ST_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);

		m_Context->InitializeContext();
		

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW WINDOW EVENTS
		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.IsMinimized = iconified == 0 ? false : true;

			WindowMinimizeEvent event;
			data.EventCallback(event);
		});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					Input::GetFrameKeyMap()[(Saturn::KeyCode)key] = Saturn::InputState::Down;
					Input::GetStateKeyMap()[(Saturn::KeyCode)key] = Saturn::InputState::Down;

					KeyPressedEvent event((Saturn::KeyCode)key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Input::GetFrameKeyMap()[(Saturn::KeyCode)key] = Saturn::InputState::Up;
					Input::GetStateKeyMap()[(Saturn::KeyCode)key] = Saturn::InputState::Up;

					KeyReleasedEvent event((Saturn::KeyCode)key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					Input::GetRepeatKeyMap()[(Saturn::KeyCode)key] = Saturn::InputState::Down;

					KeyPressedEvent event((Saturn::KeyCode)key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					Input::GetFrameMouseButtonMap()[(MouseButton)button] = InputState::Down;
					Input::GetStateMouseButtonMap()[(MouseButton)button] = InputState::Down;

					MouseButtonPressedEvent event((MouseButton)button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Input::GetFrameMouseButtonMap()[(MouseButton)button] = InputState::Up;
					Input::GetStateMouseButtonMap()[(MouseButton)button] = InputState::Up;

					MouseButtonReleasedEvent event((MouseButton)button);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			Input::MouseScrollDelta = glm::vec2((float)xOffset, (float)yOffset);

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			Input::MousePosition = glm::vec2((float)xPos, (float)yPos);

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	void WindowsWindow::Shutdown()
	{
		if (s_GLFWInitialized && m_Window)
			glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate(Time time)
	{
		ST_PROFILE_FUNCTION();

		Input::ResetKeyStates();
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		ST_PROFILE_FUNCTION();

		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
}
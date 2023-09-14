#include "saturnpch.h"
#include "WindowsInput.h"
#include "Saturn/Application.h"
#include "GLFW/glfw3.h"

namespace Saturn
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::GetKeyPressedImpl(Saturn::KeyCode keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::GetMouseButtonPressedImpl(Saturn::MouseButton button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x;
		glfwGetCursorPos(window, &x, NULL);
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double y;
		glfwGetCursorPos(window, NULL, &y);
		return y;
	}
}

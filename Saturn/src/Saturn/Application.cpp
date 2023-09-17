#include "saturnpch.h"
#include "Application.h"
#include "Core.h"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "Saturn/Input.h"
#include "glm/glm.hpp"

#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Core/Time.h"

namespace Saturn 
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ST_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scoped<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Initialize();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	inline static void GLErr(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		ST_CORE_ERROR("[OpenGL Error] 0x{0:x} - 0x{1:x} - 0x{2:x}, {3}", type, id, severity, message);
	}

	void Application::Run() 
	{
		glDebugMessageCallback(GLErr, 0);

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Time deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(deltaTime);
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
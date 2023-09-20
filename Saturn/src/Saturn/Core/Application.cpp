#include "SaturnPch.h"
#include "Saturn/Core/EntryPoint.h"
#include "Saturn/Core/Application.h"
#include "Saturn/Rendering/Renderer.h"
#include "Saturn/Core/Core.h"
#include "Saturn/Core/Time.h"

namespace Saturn 
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, UInt32 windowWidth, UInt32 windowHeight)
	{
		ST_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scoped<Window>(Window::Create({ name, windowWidth, windowHeight }));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Initialize();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run() 
	{
		ST_PROFILE_FUNCTION();
		while (m_Running)
		{
			float time = Renderer::GetTime();
			Time deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(deltaTime);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(deltaTime);
		}
	}

	void Application::OnEvent(Event& event)
	{
		ST_PROFILE_FUNCTION();
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowMinimizeEvent>(std::bind(&Application::OnWindowMinimize, this, std::placeholders::_1));

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

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() > 0 && e.GetHeight() > 0)
			m_Minimized = false;
		Renderer::OnWindowResize(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

	bool Application::OnWindowMinimize(WindowMinimizeEvent& e)
	{
		m_Minimized = true;
		return false;
	}
}
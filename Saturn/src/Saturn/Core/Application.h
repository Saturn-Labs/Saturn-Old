#pragma once
#include "Saturn/Core/Window.h"
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/Main/LayerStack.h"
#include "Saturn/Main/Layer.h"
#include "Saturn/ImGui/ImGuiLayer.h"
#include "Saturn/IO/Log.h"

namespace Saturn 
{
	class Application
	{
	public:
		Application(const std::string& name = "Saturn Application", UInt32 windowWidth = 640, UInt32 windowHeight = 360);
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static void Close()
		{
			Get().m_Running = false;
		}

		inline static Application& Get()
		{
			return *s_Instance;
		}

		inline Window& GetWindow() const
		{
			return *m_Window;
		}

		ImGuiLayer* GetImGuiLayer()
		{
			return m_ImGuiLayer;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowMinimize(WindowMinimizeEvent& e);

	private:
		Scoped<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// Please define this in the client App returning the App pointer.
	Application* CreateApplication();
}
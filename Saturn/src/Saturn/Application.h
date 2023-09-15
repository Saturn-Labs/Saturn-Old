#pragma once
#include "Window.h"

#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Events/KeyEvent.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/LayerStack.h"
#include "Saturn/Layer.h"

#include "Saturn/ImGui/ImGuiLayer.h"

#include "Rendering/Shader.h"
#include "Rendering/Buffer.h"
#include "Rendering/VertexArray.h"

namespace Saturn 
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get()
		{
			return *s_Instance;
		}

		inline Window& GetWindow() const
		{
			return *m_Window;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_BasicShader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// Please define this in the client App returning the App pointer.
	Application* CreateApplication();
}
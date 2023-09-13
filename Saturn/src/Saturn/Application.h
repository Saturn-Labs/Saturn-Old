#pragma once
#include "Window.h"

namespace Saturn 
{
	class SATURNAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window = nullptr;
		bool m_Running = true;
	};

	//to client
	Application* CreateApplication();
}
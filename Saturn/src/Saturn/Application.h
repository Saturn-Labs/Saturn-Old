#pragma once

#include "Core.h"

namespace Saturn 
{
	class SATURNAPI Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to client
	Application* CreateApplication();
}
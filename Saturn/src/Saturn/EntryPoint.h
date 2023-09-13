#pragma once
#include "Application.h"

#ifdef ST_PLATFORM_WINDOWS
extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char** argv)
{
	Saturn::Log::Initialize();
	ST_CORE_WARN("Logger initialized!");
	ST_INFO("Hello, World!");

	auto app = Saturn::CreateApplication();
	app->Run();
	delete app;
}
#endif
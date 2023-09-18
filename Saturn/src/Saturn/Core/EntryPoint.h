#pragma once
#include "Saturn/Core/Application.h"

#ifdef ST_PLATFORM_WINDOWS
extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char** argv)
{
	Saturn::Log::Initialize();

	ST_PROFILE_BEGIN_SESSION("Startup", "ST_PROFILE-Startup.json");
	auto app = Saturn::CreateApplication();
	ST_PROFILE_END_SESSION();

	ST_PROFILE_BEGIN_SESSION("Runtime", "ST_PROFILE-Runtime.json");
	app->Run();
	ST_PROFILE_END_SESSION();

	ST_PROFILE_BEGIN_SESSION("Shutdown", "ST_PROFILE-Shutdown.json");
	delete app;
	ST_PROFILE_END_SESSION();
	return 0;
}
#endif
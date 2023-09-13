#pragma once
#include "Application.h"

#ifdef ST_PLATFORM_WINDOWS
extern Saturn::Application* Saturn::CreateApplication();

int main(int argc, char** argv)
{
	printf("[Saturn Engine]");
	auto app = Saturn::CreateApplication();
	app->Run();
	delete app;
}
#endif
#include "SaturnPch.h"
#include "Saturn/IO/Log.h"

namespace Saturn
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger = nullptr;
	bool Log::s_Initialized = false;

	void Log::Initialize()
	{
		if (s_Initialized)
			return;

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Saturn");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Application");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_Initialized = true;
	}
}

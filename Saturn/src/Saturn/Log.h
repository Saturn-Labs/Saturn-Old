#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Saturn
{
	class SATURNAPI Log
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//CORE LOGGING MACROS
#define ST_CORE_TRACE(...)	  ::Saturn::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ST_CORE_INFO(...)	  ::Saturn::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ST_CORE_WARN(...)	  ::Saturn::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ST_CORE_ERROR(...)	  ::Saturn::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ST_CORE_CRITICAL(...) ::Saturn::Log::GetCoreLogger()->critical(__VA_ARGS__)

//CLIENT LOGGING MACROS
#define ST_TRACE(...)		  ::Saturn::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ST_INFO(...)		  ::Saturn::Log::GetClientLogger()->info(__VA_ARGS__)
#define ST_WARN(...)		  ::Saturn::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ST_ERROR(...)		  ::Saturn::Log::GetClientLogger()->error(__VA_ARGS__)
#define ST_CRITICAL(...)	  ::Saturn::Log::GetClientLogger()->critical(__VA_ARGS__)
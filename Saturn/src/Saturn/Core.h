#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 1

#ifdef ST_PLATFORM_WINDOWS
	#if ST_BUILD_DLL
		#define SATURNAPI __declspec(dllexport)
	#else
		#define SATURNAPI __declspec(dllimport)
	#endif
#else
	#error Saturn only supports windows.
#endif

#ifdef ST_ENABLE_ASSERTS
	#define ST_ASSERT(x, ...) { if (!(x)) { ST_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ST_CORE_ASSERT(x, ...) { if (!(x)) { ST_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ST_ASSERT(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define ST_BIND_EVENTFN(fn) std::bind(fn, this, std::placeholders::_1)
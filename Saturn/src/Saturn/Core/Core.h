#pragma once
#include "Saturn/Common/Types.h"
#include <memory>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 1

#ifndef ST_PLATFORM_WINDOWS
	#error Saturn only supports windows.
#endif

#ifdef ST_DEBUG
	#define ST_ENABLE_ASSERTS
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

namespace Saturn
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scoped = std::unique_ptr<T>;
};
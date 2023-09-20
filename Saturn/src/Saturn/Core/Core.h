#pragma once
#include "Saturn/Common/Types.h"
#include "Saturn/IO/Log.h"
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
	template<typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using WeakRef = std::weak_ptr<T>;
	template<typename T>
	constexpr WeakRef<T> GetWeakRef(Ref<T> ref)
	{
		return ref;
	}

	template<typename T>
	using Scoped = std::unique_ptr<T>;
	template<typename T, typename... Args>
	constexpr Scoped<T> CreateScoped(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
};
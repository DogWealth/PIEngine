#pragma once

#include <memory>

#ifdef PI_PLATFORM_WINDOWS
#if PI_DYNAMIC_LINK
	#ifdef PI_BUILD_DLL
		#define PI_API __declspec(dllexport)
	#else
		#define PI_API __declspec(dllimport)
	#endif
#else
	#define PI_API
#endif
#else
	#error PIEngine only support windows!
#endif

#ifdef PI_DEBUG
	#define PI_ENABLE_ASSERTS
#endif // PI_DEBUG


#ifdef PI_ENABLE_ASSERTS
	#define PI_ASSERT(x, ...) {if(!(x)) {PI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
	#define PI_CORE_ASSERT(x, ...) {if(!(x)) {PI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define PI_ASSERT(x, ...)
	#define PI_CORE_ASSERT(x, ...)
#endif // PI_ENABLE_ASSERTS


#define BIT(x) (1 << x)
#define PI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace PIEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
#pragma once

#ifdef PI_PLATFORM_WINDOWS
	#ifdef PI_BUILD_DLL
		#define PI_API __declspec(dllexport)
	#else
		#define PI_API __declspec(dllimport)
	#endif
#else
	#error PIEngine only support windows!
#endif

#ifdef PI_ENABLE_ASSERTS
	#define PI_ASSERT(x, ...) {if(!(x)) {PI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
	#define PI_CORE_ASSERT(x, ...) {if(!(x)) {PI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
	#define PI_ASSERT(x, ...)
	#define PI_CORE_ASSERT(x, ...)
#endif // PI_ENABLE_ASSERTS


#define BIT(x) (1 << x)
#define PI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
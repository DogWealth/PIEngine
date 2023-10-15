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

#define BIT(x) (1 << x)
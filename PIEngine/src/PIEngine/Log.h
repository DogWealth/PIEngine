#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace PIEngine {
	class PI_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define PI_CORE_ERROR(...)	::PIEngine::Log::GetCoreLogger()->error(__VA_ARGS__) //https://blog.csdn.net/bat67/article/details/77542165
#define PI_CORE_WARN(...)	::PIEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PI_CORE_INFO(...)	::PIEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PI_CORE_TRACE(...)	::PIEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PI_CORE_FATAL(...)	::PIEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define PI_ERROR(...)		::PIEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PI_WARN(...)		::PIEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PI_INFO(...)		::PIEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PI_TRACE(...)		::PIEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PI_FATAL(...)		::PIEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
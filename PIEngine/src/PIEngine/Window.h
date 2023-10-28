#pragma once
#include "pipch.h"

#include "PIEngine/Core.h"
#include "PIEngine/Events/Event.h"

namespace PIEngine {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "PI Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{

		}
	};

	//接口，在每个平台上win，linux，mac都要实现
	class PI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;//void* 是因为具体实现不同，不一定是GLFWwindow，也肯是其他库来实现

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
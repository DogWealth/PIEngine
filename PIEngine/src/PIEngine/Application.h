#pragma once
#include "Core.h"
#include "PIEngine\Events\Event.h"
#include "PIEngine/LayerStack.h"
#include "Window.h"
#include "PIEngine/Events/ApplicationEvent.h"

namespace PIEngine {

	class PI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// �ڿͻ��˶���
	Application* CreatApplication();
}


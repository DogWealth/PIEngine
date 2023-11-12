#pragma once
#include "Core.h"
#include "PIEngine\Events\Event.h"
#include "PIEngine/LayerStack.h"
#include "Window.h"
#include "PIEngine/Events/ApplicationEvent.h"
#include "PIEngine/ImGui/ImGuiLayer.h"
#include "PIEngine/Renderer/Shader.h"
#include "PIEngine/Renderer/Buffer.h"
#include "PIEngine/Renderer/VertexArray.h"
#include "PIEngine/Renderer/OrthographicCamera.h"

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

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		//std::unique_ptr<ImGuiLayer> m_ImGuiLayer;//所有权要转移到layerstack，不能用unique_ptr
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// 在客户端定义
	Application* CreatApplication();
}


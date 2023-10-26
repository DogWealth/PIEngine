#pragma once

#include "PIEngine/Layer.h"
#include "PIEngine/Events/MouseEvent.h"
#include "PIEngine/Events/KeyEvent.h"
#include "PIEngine/Events/ApplicationEvent.h"
namespace PIEngine
{
	class PI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyTypedEvnet(KeyTypedEvent& e);

	private:
		float m_Time = 0.0f;
	};

}

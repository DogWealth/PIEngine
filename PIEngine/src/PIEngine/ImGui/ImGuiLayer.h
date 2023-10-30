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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}

#pragma once
#include "Core.h"
#include "Events/Event.h"
namespace PIEngine {

	class PI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// �ڿͻ��˶���
	Application* CreatApplication();
}


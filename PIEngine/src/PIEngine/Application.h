#pragma once
#include "Core.h"
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


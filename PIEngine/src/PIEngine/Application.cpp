#include "pipch.h"
#include "Application.h"
#include "PIEngine/Events/ApplicationEvent.h"
#include "PIEngine/Log.h"
PIEngine::Application::Application()
{
}

PIEngine::Application::~Application()
{
}

void PIEngine::Application::Run()
{
	WindowResizeEvent e(1280, 720);
	PI_TRACE(e);
}


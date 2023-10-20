#include "pipch.h"
#include "Application.h"
#include "PIEngine/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"
PIEngine::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
}

PIEngine::Application::~Application()
{
}

void PIEngine::Application::Run()
{
	while (m_Running)
	{
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Window->OnUpdate();
	}
}


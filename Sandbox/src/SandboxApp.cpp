#include<PIEngine.h>

class ExampleLayer : public PIEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{

		if (PIEngine::Input::IsKeyPressed(PI_KEY_TAB))
			PI_TRACE("Tab key is pressed(poll)!");
	}

	void OnEvent(PIEngine::Event& event) override
	{
		if (event.GetEventType() == PIEngine::EventType::KeyPressed)
		{
			if (PIEngine::Input::IsKeyPressed(PI_KEY_TAB))
				PI_TRACE("Tab key is pressed(event)!");
		}
	}
};

class Sandbox : public PIEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new PIEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

PIEngine::Application* PIEngine::CreatApplication()
{
	return new Sandbox();
}

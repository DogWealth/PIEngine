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
		PI_INFO("ExampleLayer::Update");
	}

	void OnEvent(PIEngine::Event& event) override
	{
		PI_TRACE("{0}", event);
	}
};

class Sandbox : public PIEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

PIEngine::Application* PIEngine::CreatApplication()
{
	return new Sandbox();
}

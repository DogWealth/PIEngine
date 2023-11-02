#include<PIEngine.h>
#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, PI");
		ImGui::End();

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
	}

	~Sandbox()
	{

	}
};

PIEngine::Application* PIEngine::CreatApplication()
{
	return new Sandbox();
}

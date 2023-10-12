#include<PIEngine.h>

class Sandbox : public PIEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

PIEngine::Application* PIEngine::CreatApplication()
{
	return new Sandbox();
}

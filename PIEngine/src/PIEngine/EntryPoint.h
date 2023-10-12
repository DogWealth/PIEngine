#pragma once
#ifdef PI_PLATFORM_WINDOWS

extern PIEngine::Application* PIEngine::CreatApplication();

int main(int arc, char** argv)
{
	PIEngine::Log::Init();
	PI_CORE_WARN("Initialized Log!");
	PI_INFO("Hello PI!");

	auto app = PIEngine::CreatApplication();
	app->Run();
	delete app;
}
#endif // PI_PLATFORM_WINDOWS

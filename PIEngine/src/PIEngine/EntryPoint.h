#pragma once
#ifdef PI_PLATFORM_WINDOWS

extern PIEngine::Application* PIEngine::CreatApplication();

int main(int arc, char** argv)
{
	printf("PI Engine!\n");
	auto app = PIEngine::CreatApplication();
	app->Run();
	delete app;
}
#endif // PI_PLATFORM_WINDOWS

#pragma once

#ifdef HL_PLATFORM_WINDOWS

extern Heirloom::Application* Heirloom::CreateApplication();

int main(int arc, char** argv)
{
	Heirloom::Log::Init();
	HL_CORE_WARN("Initialized Log!");
	HL_INFO("Hello! 123");
	
	Heirloom::Application* app = Heirloom::CreateApplication();
	app->Run();
	delete app;

	return EXIT_SUCCESS;
}

#endif
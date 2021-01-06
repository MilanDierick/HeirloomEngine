#pragma once

#ifdef HL_PLATFORM_WINDOWS

extern Heirloom::Application* Heirloom::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int arc, char** argv)
{
	Heirloom::Log::Init();
	HL_CORE_INFO("Initialized Log!");

	Heirloom::Application* app = Heirloom::CreateApplication();
	app->Run();
	delete app;

	return EXIT_SUCCESS;
}

#endif

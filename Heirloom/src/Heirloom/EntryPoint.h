#pragma once

#ifdef HL_PLATFORM_WINDOWS

extern Heirloom::Application* Heirloom::CreateApplication();

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main()
{
	Heirloom::Log::Init();
	HL_CORE_INFO("Initialized Log!");

	Heirloom::Application* app = Heirloom::CreateApplication();

	try
	{
		app->Run();
	}
	catch (std::exception& exception)
	{
		HL_CORE_FATAL(exception.what());
	}
	
	delete app;

	return EXIT_SUCCESS;
}

#endif

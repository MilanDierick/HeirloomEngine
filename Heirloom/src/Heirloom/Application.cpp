#include "hlpch.h"
#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Heirloom
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		const WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HL_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HL_TRACE(e);
		}

		while (true);
	}
}

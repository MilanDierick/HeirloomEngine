#include "Heirloom.h"

class Sandbox final : public Heirloom::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	return new Sandbox();
}
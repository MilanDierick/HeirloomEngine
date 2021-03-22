#include "hlpch.h"
#include "GameObject.h"
void Heirloom::GameObject::Update(const Timestep ts)
{
	HL_PROFILE_FUNCTION()
	
	for (auto [key, component] : m_Components)
	{
		component->Update(ts);
	}
}

void Heirloom::GameObject::Render() const
{
	HL_PROFILE_FUNCTION()
	
	for (auto [key, component] : m_Components)
	{
		component->Render();
	}
}

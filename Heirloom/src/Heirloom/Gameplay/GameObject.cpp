#include "hlpch.h"
#include "GameObject.h"
void Heirloom::GameObject::Update(const Timestep ts)
{
	for (auto [key, component] : m_Components)
	{
		component->Update(ts);
	}
}

void Heirloom::GameObject::Render() const
{
	for (auto [key, component] : m_Components)
	{
		component->Render();
	}
}

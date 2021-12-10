//
// Created by developer on 09/12/2021.
//

#include "GameObject.h"

namespace Heirloom
{
	void GameObject::Update(const Timestep ts)
	{
		HL_PROFILE_FUNCTION()

		for (auto [key, component] : m_Components)
		{
			component->Update(ts);
		}
	}

	void GameObject::Render() const
	{
		HL_PROFILE_FUNCTION()

		for (auto [key, component] : m_Components)
		{
			component->Render();
		}
	}
}
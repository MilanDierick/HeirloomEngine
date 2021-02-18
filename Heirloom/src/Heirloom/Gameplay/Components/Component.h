#pragma once
#include "Heirloom/Core/Timestep.h"

namespace Heirloom
{
	class Component
	{
	public:
		virtual ~Component() = default;
		
		virtual void Update(Timestep ts) = 0;
		virtual void Render() const = 0;
	};
}

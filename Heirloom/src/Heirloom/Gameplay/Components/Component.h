#pragma once
#include "Heirloom/Core/Timestep.h"

namespace Heirloom
{
	class Component
	{
	public:
		virtual ~Component() = default;

		virtual uint32_t GetID() const = 0;
		
		virtual void Update(Timestep ts) = 0;
		virtual void Render() const = 0;
	};
}

//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_COMPONENT_H
#define HEIRLOOM_COMPONENT_H

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


#endif //HEIRLOOM_COMPONENT_H

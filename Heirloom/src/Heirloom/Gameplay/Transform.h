#pragma once

#include "Heirloom/Core.h"

namespace Heirloom
{
	struct Transform
	{
		Transform();
		Transform(Position position, Scale scale);
		
		const Position& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(Position position);
		const Scale& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
		void SetScale(Scale scale);
	
	private:
		Position m_Position;
		Scale m_Scale;
	};
}

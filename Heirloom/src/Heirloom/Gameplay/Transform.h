#pragma once

#include "Components/Component.h"

#include "Heirloom/Core.h"

namespace Heirloom
{
	class Transform final : Component
	{
	public:
		Transform();
		Transform(Position position, Scale scale);
		
		[[nodiscard]] const Position& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(Position position);
		[[nodiscard]] const Scale& GetScale() const { return m_Scale; }
		void SetScale(float x, float y, float z);
		void SetScale(Scale scale);

		void Update(Timestep ts) override;
		void Render() const override;
	
	private:
		Position m_Position;
		Scale m_Scale;
	};
}

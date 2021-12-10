// Author: Milan Dierick
// Solution: Heirloom

//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_TRANSFORM_H
#define HEIRLOOM_TRANSFORM_H

#include "Components/Component.h"
#include "glm/vec3.hpp"

namespace Heirloom
{
	class Transform final : Component
	{
	public:
		Transform();
		Transform(glm::vec3 position, glm::vec3 scale);

		[[nodiscard]] const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);
		[[nodiscard]] const glm::vec3& GetScale() const;
		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);

		void Update(Timestep ts) override;
		void Render() const override;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
	};
}

#endif //HEIRLOOM_TRANSFORM_H

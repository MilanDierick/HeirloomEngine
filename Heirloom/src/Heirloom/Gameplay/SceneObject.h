#pragma once
#include "Heirloom/Core/Timestep.h"

namespace Heirloom
{
	class SceneObject
	{
	public:
		SceneObject()          = default;
		virtual ~SceneObject() = default;

		SceneObject(const SceneObject& other)                = delete;
		SceneObject(SceneObject&& other) noexcept            = delete;
		SceneObject& operator=(const SceneObject& other)     = delete;
		SceneObject& operator=(SceneObject&& other) noexcept = delete;

		virtual void Update(Timestep ts) = 0;
		virtual void Render() const = 0;
	};
}

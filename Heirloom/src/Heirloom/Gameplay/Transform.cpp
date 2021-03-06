#include "hlpch.h"
#include "Transform.h"

Heirloom::Transform::Transform() : m_Position(0.0f), m_Scale(0.0f) {}
Heirloom::Transform::Transform(const glm::vec3 position, const glm::vec3 scale) : m_Position(position), m_Scale(scale) {}

void Heirloom::Transform::SetPosition(const float x, const float y, const float z)
{
	SetPosition({x, y, z});
}

void Heirloom::Transform::SetPosition(const glm::vec3 position)
{
	m_Position = position;
}

void Heirloom::Transform::SetScale(const float x, const float y, const float z)
{
	SetScale({x, y, z});
}

void Heirloom::Transform::SetScale(const glm::vec3 scale)
{
	m_Scale = scale;
}

void Heirloom::Transform::Update(Timestep)
{
	
}

void Heirloom::Transform::Render() const
{
	
}

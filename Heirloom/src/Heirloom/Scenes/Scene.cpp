#include "hlpch.h"
#include "Scene.h"

Heirloom::Scene::Scene(const std::string sceneName)
	: m_IsActive(false), m_SceneName(sceneName)
{
}

bool Heirloom::Scene::IsActive() const { return m_IsActive; }

void Heirloom::Scene::SetActive(const bool active)
{
	m_IsActive = active;
}

std::string Heirloom::Scene::GetName() const { return m_SceneName; }

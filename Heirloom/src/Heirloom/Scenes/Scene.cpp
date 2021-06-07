#include "hlpch.h"
#include "Scene.h"

Heirloom::Scene::Scene(std::string sceneName)
	: m_IsActive(false), m_SceneName(sceneName)
{
}

bool Heirloom::Scene::IsActive() const { return m_IsActive; }

std::string Heirloom::Scene::GetName() const { return m_SceneName; }

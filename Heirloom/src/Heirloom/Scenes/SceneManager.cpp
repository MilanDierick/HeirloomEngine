#include "hlpch.h"
#include "SceneManager.h"

#include "Scene.h"
#include "Heirloom/Core/Layer.h"

namespace Heirloom
{
	void SceneManager::SaveScene() { throw std::exception("Not implemented!"); }

	std::future<bool> SceneManager::LoadScene(std::string sceneName, const bool cacheCurrentScene)
	{
		if (!cacheCurrentScene) { RemoveScene(sceneName); }

		return std::async(std::launch::async, LoadSceneFromDisk, std::forward<std::string>(sceneName));
	}

	bool SceneManager::LoadScene(Scope<Scene> newScene, const bool cacheCurrentScene)
	{
		if (!cacheCurrentScene) { RemoveScene(newScene->GetName()); }

		const std::array<Scope<Scene>, MAX_CONCURRENT_LOADED_SCENES>::iterator it = std::ranges::find_if(m_SceneCache,
			[=](Scope<Scene>& scene) { return scene == nullptr; });

		if (it != std::end(m_SceneCache))
		{
			*it = CreateScope<Scene>(std::move(newScene));
			return true;
		}

		HL_CORE_ERROR("Trying to load scene while there are already a maximum of {0} scenes loaded!",
					  MAX_CONCURRENT_LOADED_SCENES);
		return false;
	}

	bool SceneManager::AddLayerToActiveScene(const Ref<Layer> layer)
	{
		const std::array<Scope<Scene>, MAX_CONCURRENT_LOADED_SCENES>::iterator it = std::ranges::find_if(m_SceneCache,
			[=](Scope<Scene>& scene) { return scene->IsActive() == true; });

		if (it != std::end(m_SceneCache))
		{
			(*it)->AddLayer(layer);
			return true;
		}

		HL_CORE_ERROR("Failed to add layer with name \"{0}\" to scene with name \"{1}\"",
					  layer->GetName(),
					  (*it)->GetName());
		return false;
	}

	bool SceneManager::RemoveLayerFromActiveScene(const Ref<Layer> layer)
	{
		const std::array<Scope<Scene>, MAX_CONCURRENT_LOADED_SCENES>::iterator it = std::ranges::find_if(m_SceneCache,
			[=](Scope<Scene>& scene) { return scene->IsActive() == true; });

		if (it != std::end(m_SceneCache))
		{
			(*it)->RemoveLayer(layer);
			return true;
		}

		HL_CORE_ERROR("Failed to remove layer with name \"{0}\" from scene with name \"{1}\"",
					  layer->GetName(),
					  (*it)->GetName());
		return false;
	}

	bool SceneManager::LoadSceneFromDisk(std::string sceneName) { throw std::exception("Not implemented!"); }

	bool SceneManager::RemoveScene(const std::string sceneName)
	{
		const std::array<Scope<Scene>, MAX_CONCURRENT_LOADED_SCENES>::iterator it = std::ranges::find_if(m_SceneCache,
			[=](Scope<Scene>& scene) { return scene->GetName() == sceneName; });

		if (it != std::end(m_SceneCache))
		{
			it->reset(nullptr);
			return true;
		}

		HL_CORE_ERROR("Scene with name {0} designated to be removed could not be found!", sceneName);
		return false;
	}
}

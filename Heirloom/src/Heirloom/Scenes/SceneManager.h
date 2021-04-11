// Author: Milan Dierick
// Created: 11/04/2021 6:23 PM
// Solution: HeirloomEngine

#pragma once

// Save scene
// Load scene
// Add scene
// Remove scene

#define MAX_CONCURRENT_LOADED_SCENES 8
#include <future>

namespace Heirloom
{
	class Timestep;
	class Scene;
	class Layer;

	class SceneManager
	{
	public:
		static void SaveScene(); // Should save a scene to disk, this is currently not supported
		static std::future<bool> LoadScene(std::string sceneName, bool cacheCurrentScene = false);
		static bool LoadScene(Scope<Scene> newScene, bool cacheCurrentScene = false);

		static bool AddLayerToActiveScene(Ref<Layer> layer);
		static bool RemoveLayerFromActiveScene(Ref<Layer> layer);

		static void UpdateScenes(Timestep timestep);

	private:
		static bool LoadSceneFromDisk(std::string sceneName);
		static bool RemoveScene(std::string sceneName);

		static std::array<Scope<Scene>, MAX_CONCURRENT_LOADED_SCENES> m_SceneCache;
	};
}

// Author: Milan Dierick
// Created: 11/04/2021 6:24 PM
// Solution: HeirloomEngine

#pragma once

namespace Heirloom
{
	class Layer;

	class Scene
	{
	public:
		explicit Scene(std::string sceneName);

		void AddLayer(Ref<Layer> layer);
		void RemoveLayer(Ref<Layer> layer);
		
		bool IsActive() const;
		std::string GetName() const;

	private:
		bool m_IsActive;
		std::string m_SceneName;
	};
}

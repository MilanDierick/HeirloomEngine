#pragma once
#include <map>
#include <typeindex>
#include "SceneObject.h"
#include "Transform.h"
#include "Components/Component.h"

namespace Heirloom
{
	// TODO: We can only add a single component of each type to a game object, we need to be able to add multiple components per type, fix this
	class GameObject final : SceneObject
	{
	public:
		GameObject()          = default;
		virtual ~GameObject() = default;

		// Copy & move operations
		GameObject(const GameObject& other)                = delete;
		GameObject(GameObject&& other) noexcept            = delete;
		GameObject& operator=(const GameObject& other)     = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		// ReSharper disable once CppMemberFunctionMayBeConst
		[[nodiscard]] Ref<Transform> GetTransform() { return m_Transform; }

		void Update(Timestep ts) override;
		void Render() const override;

		template <typename ComponentType = Component>
		Ref<ComponentType> AddComponent(ComponentType* component);

		template <typename ComponentType = Component>
		[[nodiscard]] Ref<ComponentType> GetComponent();

		template <typename ComponentType = Component>
		bool RemoveComponent(ComponentType component);

	private:
		Ref<Transform> m_Transform;
		std::map<std::type_index, Component*> m_Components;
	};

	template <typename ComponentType>
	Ref<ComponentType> GameObject::AddComponent(ComponentType* component)
	{
		const std::pair<std::map<uint32_t, Component*>::iterator, bool> value = m_Components.
			emplace(typeid(ComponentType), component);

		HL_CORE_TRACE("Added component of type {0} to game object", typeid(ComponentType));
		return value.second ? value.first->second : nullptr;
	}

	template <typename ComponentType>
	Ref<ComponentType> GameObject::GetComponent()
	{
		try
		{
			return m_Components.at(typeid(ComponentType));
		}
		catch (std::out_of_range& exception)
		{
			HL_CORE_WARN("Tried accessing non-existing component in gameobject!");
			return nullptr;
		}
	}

	template <typename ComponentType>
	bool GameObject::RemoveComponent(ComponentType component)
	{
		HL_CORE_TRACE("Removed component of type {0} from game object", typeid(ComponentType));
		return static_cast<bool>(m_Components.erase(typeid(component)));
	}
}

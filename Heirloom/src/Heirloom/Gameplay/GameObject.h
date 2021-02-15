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
		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other)                = delete;
		GameObject(GameObject&& other) noexcept            = delete;
		GameObject& operator=(const GameObject& other)     = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		// This probably shouldn't be const, but lets keep it this way until we come across a situation where we want to change 
		Ref<Transform> GetTransform() const;

		void Update(Timestep ts) override;
		void Render() const override;

		template <typename T = Component>
		Ref<T> AddComponent(T component);

		template <typename T = Component>
		Ref<T> GetComponent(T component);

		template <typename T = Component>
		bool RemoveComponent(T component);

	private:
		Ref<Transform> m_Transform;
		std::map<std::type_index, Ref<Component>> m_Components;
	};

	template <typename T>
	Ref<T> GameObject::AddComponent(T component)
	{
		const std::pair<std::map<std::type_index, Ref<Component>>::iterator, bool> value = m_Components.
			insert(std::make_shared<T>(component));

		return value.second ? value.first->second : nullptr;
	}

	template <typename T>
	Ref<T> GameObject::GetComponent(T component)
	{
		try
		{
			return m_Components.at(typeid(component));
		}
		catch (std::out_of_range& exception)
		{
			HL_CORE_WARN("Tried accessing non-existing component in gameobject!");
			return nullptr;
		}
	}

	template <typename T>
	bool GameObject::RemoveComponent(T component)
	{
		return static_cast<bool>(m_Components.erase(typeid(component)));
	}
}

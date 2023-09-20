#pragma once
#include <entt.hpp>
#include "../Scene.h"
#include "Saturn/Core/Core.h"
#include "../Components/Transform.h"
#include "../Components/Tag.h"

namespace Saturn
{
	class Entity
	{
		friend class Scene;
	public:
		Entity(entt::entity handle, Scene* scene);
		Entity() = default;
		Entity(const Entity&) = default;

		template<typename Component>
		bool HasComponent() const
		{
			if (!m_SceneReference)
				return false;
			return m_SceneReference->m_Registry.all_of<Component>(m_EntityHandle);
		}

		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			ST_CORE_ASSERT(!HasComponent<Component>(), "Entity already has component!");
			return m_SceneReference->m_Registry.emplace<Component>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename Component>
		Component& GetComponent()
		{
			ST_CORE_ASSERT(HasComponent<Component>(), "Entity doesn't have the component!");
			return m_SceneReference->m_Registry.get<Component>(m_EntityHandle);
		}

		template<typename Component>
		void RemoveComponent()
		{
			ST_CORE_ASSERT(HasComponent<Component>(), "Entity doesn't have the component!");
			m_Scene->m_Registry.remove<Component>(m_EntityHandle);
		}

		operator bool() const
		{
			return m_EntityHandle != entt::null;
		}

		Component::Transform& GetTransform()
		{
			if (!m_Transform)
			{
				if (HasComponent<Component::Transform>())
					m_Transform = &GetComponent<Component::Transform>();
				else
					m_Transform = &AddComponent<Component::Transform>();
			}
			return *m_Transform;
		}
		Component::Tag& GetTag()
		{
			if (!m_Tag)
			{
				if (HasComponent<Component::Tag>())
					m_Tag = &GetComponent<Component::Tag>();
				else
					m_Tag = &AddComponent<Component::Tag>();
			}
			return *m_Tag;
		}

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_SceneReference = nullptr;

		Component::Transform* m_Transform = nullptr;
		Component::Tag* m_Tag = nullptr;
	};
}
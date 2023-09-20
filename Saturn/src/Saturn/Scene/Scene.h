#pragma once
#include <entt.hpp>
#include "Saturn/Core/Time.h"
#include "Saturn/Common/Types.h"

namespace Saturn
{
	class Entity;

	class Scene
	{
		friend class Entity;
		friend class SceneHierarchyPanel;
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "My Entity", 
			const Vector3& Position = Vector3 { 0.0f, 0.0f, 0.0f },
			const Vector3& Rotation = Vector3 { 0.0f, 0.0f, 0.0f },
			const Vector3& Scale = Vector3 { 1.0f, 1.0f, 1.0f });
		void RemoveEntity(Entity entity);

		void OnUpdate(Time time);
		void OnViewportResize(UInt32 width, UInt32 height);

		void OnConstructComponent(entt::registry& registry, entt::entity entity);
		void OnDestroyComponent(entt::registry& registry, entt::entity entity);
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;

		UInt32 m_ViewportWidth = 0;
		UInt32 m_ViewportHeight = 0;
	};
}
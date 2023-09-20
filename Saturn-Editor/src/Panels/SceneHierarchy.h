#pragma once
#include "Saturn/Scene/Scene.h"
#include "Saturn/Core/Core.h"
#include "Saturn/Scene/Components/Tag.h"
#include "Saturn/Scene/Components/CameraComponent.h"
#include "Saturn/Scene/Components/SpriteRenderer.h"
#include "Saturn/Scene/Entity/Entity.h"

namespace Saturn
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		void OnImGuiRender();
	private:

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

		friend class Scene;
	};
}
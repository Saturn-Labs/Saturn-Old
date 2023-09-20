#include "SaturnPch.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include "Components/Transform.h"
#include "Components/Tag.h"
#include "Components/SpriteRenderer.h"
#include "Components/CameraComponent.h"
#include "Saturn/Rendering/Renderer2D.h"
#include "Entity/Entity.h"

namespace Saturn
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name, const Vector3& Position, const Vector3& Rotation, const Vector3& Scale)
	{
		Entity entity = Entity(m_Registry.create(), this);
		entity.AddComponent<Component::Tag>(name);
		entity.AddComponent<Component::Transform>(Position, Rotation, Scale);
		return entity;
	}

	void Scene::OnUpdate(Time time)
	{
		Component::CameraComponent* mainCameraComponent = nullptr;
		Component::Transform* mainCameraTransform = nullptr;
		{
			auto view = m_Registry.view<Component::Transform, Component::CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<Component::Transform, Component::CameraComponent>(entity);

				if (camera.Main)
				{
					mainCameraComponent = &camera;
					mainCameraTransform = &transform;
					break;
				}
			}
		}

		if (mainCameraComponent && mainCameraTransform)
		{
			Renderer2D::BeginScene(TransformedCamera(*mainCameraTransform, *mainCameraComponent));

			{
				auto group = m_Registry.group<Component::Transform>(entt::get<Component::SpriteRenderer>);
				for (auto entity : group)
				{
					auto& [transform, spriteRenderer] = group.get<Component::Transform, Component::SpriteRenderer>(entity);
					Renderer2D::DrawQuad(transform, spriteRenderer);
				}
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(UInt32 width, UInt32 height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//Resize all non fixed aspect cameras

		auto view = m_Registry.view<Component::CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<Component::CameraComponent>(entity);
			if (!cameraComponent.FixedAspect)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}
}
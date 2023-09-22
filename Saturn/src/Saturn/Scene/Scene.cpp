#include "SaturnPch.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include "Components/Transform.h"
#include "Components/Tag.h"
#include "Components/SpriteRenderer.h"
#include "Components/CameraComponent.h"
#include "Components/NativeScript.h"
#include "Saturn/Rendering/Renderer2D.h"
#include "Entity/Entity.h"

namespace Saturn
{
	Scene::Scene()
	{
		m_Registry.on_construct<Component::NativeScript>().connect<&Scene::OnConstructComponent>(this);
		m_Registry.on_destroy<Component::NativeScript>().connect<&Scene::OnDestroyComponent>(this);
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

	void Scene::RemoveEntity(Entity entity)
	{
		m_Registry.destroy(entity);
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

		{
			m_Registry.view<Component::NativeScript>().each([=](auto entity, Component::NativeScript& nativeScript)
			{
				if (nativeScript.Behaviour)
				{
					nativeScript.OnUpdate(time);
				}
			});
		}

		if (mainCameraComponent && mainCameraTransform)
		{
			Renderer2D::BeginScene(TransformedCamera(*mainCameraTransform, *mainCameraComponent));

			{
				auto group = m_Registry.group<Component::Transform>(entt::get<Component::SpriteRenderer>);
				for (auto entity : group)
				{
					auto [transform, spriteRenderer] = group.get<Component::Transform, Component::SpriteRenderer>(entity);
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

	void Scene::OnConstructComponent(entt::registry& registry, entt::entity entity)
	{
		registry.view<Component::NativeScript>().each([=](auto entity, Component::NativeScript& nativeScript)
		{
			if (nativeScript.Behaviour)
			{
				nativeScript.OnCreate();
			}
		});
	}
	void Scene::OnDestroyComponent(entt::registry& registry, entt::entity entity)
	{
		registry.view<Component::NativeScript>().each([=](auto entity, Component::NativeScript& nativeScript)
		{
			if (nativeScript.Behaviour)
			{
				nativeScript.OnDestroy();
			}
		});
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<Component::Transform>(Entity entity, Component::Transform& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<Component::Tag>(Entity entity, Component::Tag& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<Component::SpriteRenderer>(Entity entity, Component::SpriteRenderer& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<Component::NativeScript>(Entity entity, Component::NativeScript& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<Component::CameraComponent>(Entity entity, Component::CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	Entity Scene::GetMainCamera()
	{
		auto view = m_Registry.view<Component::CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<Component::CameraComponent>(entity);
			if (camera.Main)
				return Entity(entity, this);
		}
		return {};
	}
}
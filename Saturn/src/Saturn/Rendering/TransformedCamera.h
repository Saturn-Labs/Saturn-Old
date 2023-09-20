#pragma once
#include "Saturn/Scene/Components/Transform.h"
#include "Saturn/Scene/Components/CameraComponent.h"

namespace Saturn
{
	struct TransformedCamera
	{
		TransformedCamera() = delete;
		TransformedCamera(Component::Transform& transform, Component::CameraComponent& camera)
			: TransformComponent(transform), CameraComponent(camera) { }

		Component::Transform& TransformComponent;
		Component::CameraComponent& CameraComponent;
	};
}
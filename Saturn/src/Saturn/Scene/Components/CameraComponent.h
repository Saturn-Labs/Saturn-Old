#pragma once
#include "Saturn/Camera/SceneCamera.h"

namespace Saturn::Component
{
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Main = true;
		bool FixedAspect = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}
#pragma once
#include "Saturn/Common/Types.h"

namespace Saturn::Component
{
	struct Transform
	{
		Vector3 Position = Vector3(0.0f);
		Vector3 Rotation = Vector3(0.0f);
		Vector3 Scale = Vector3(1.0f);

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
			: Position(position), Rotation(rotation), Scale(scale) { }
	};
}
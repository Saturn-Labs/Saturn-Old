#pragma once
#include "Saturn/Common/Types.h"

namespace Saturn
{
	class Camera
	{
	public:
		Camera(const Matrix4x4& projection)
			: m_Projection(projection) { }
		Camera() = default;

		virtual ~Camera() = default;

		const Matrix4x4& GetProjection() const
		{
			return m_Projection;
		}

		// TODO:
		// SetPerspective
		// SetType
		// ETC...
	protected:
		Matrix4x4 m_Projection = Matrix4x4(1.0f);
	};
}
#pragma once
#include "Saturn/Camera/Camera.h"

namespace Saturn
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera();

		void SetOrtho(float size, float zNear, float zFar);
		void SetViewportSize(UInt32 width, UInt32 height);
		float GetOrthoSize() const
		{
			return m_OrthoSize;
		}
		void SetOrthoSize(float x)
		{
			m_OrthoSize = x;
			RecalculateProjection();
		}
	private:
		void RecalculateProjection();
	private:
		float m_OrthoSize = 5.0f;
		float m_OrthoNear = -1.0f;
		float m_OrthoFar = 1.0f;

		float m_AspectRatio = 1.777777777777778f;
	};
}
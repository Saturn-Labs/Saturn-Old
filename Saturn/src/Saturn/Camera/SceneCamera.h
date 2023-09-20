#pragma once
#include "Saturn/Camera/Camera.h"
#include "Saturn/Common/Types.h"

namespace Saturn
{
	enum class CameraProjectionType
	{
		Orthographic = 0,
		Perspective = 1
	};

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera();

		CameraProjectionType GetCameraProjectionType() const
		{
			return m_CameraType;
		}
		void SetCameraProjectionType(CameraProjectionType type)
		{
			m_CameraType = type;
			RecalculateProjection();
		}
		
		float GetOrthoSize() const
		{
			return m_OrthoSize;
		}
		float GetOrthoNearClip() const
		{
			return m_OrthoNear;
		}
		float GetOrthoFarClip() const
		{
			return m_OrthoFar;
		}

		void SetOrtho(float size, float zNear, float zFar);
		void SetOrthoSize(float x)
		{
			m_OrthoSize = x;
			RecalculateProjection();
		}
		void SetOrthoNearClip(float zNear)
		{
			m_OrthoNear = zNear;
			RecalculateProjection();
		}
		void SetOrthoFarClip(float zFar)
		{
			m_OrthoFar = zFar;
			RecalculateProjection();
		}
		void SetViewportSize(UInt32 width, UInt32 height);

		//============================================================

		float GetPerspectiveVerticalFOV() const
		{
			return m_PerspectiveFOV;
		}
		float GetPerspectiveNearClip() const
		{
			return m_PerspectiveNear;
		}
		float GetPerspectiveFarClip() const
		{
			return m_PerspectiveFar;
		}

		void SetPerspective(float vFov, float zNear, float zFar);
		void SetPerspectiveVerticalFOV(float fov)
		{
			m_PerspectiveFOV = fov;
			RecalculateProjection();
		}
		void SetPerspectiveNearClip(float zNear)
		{
			m_PerspectiveNear = zNear;
			RecalculateProjection();
		}
		void SetPerspectiveFarClip(float zFar)
		{
			m_PerspectiveFar = zFar;
			RecalculateProjection();
		}

	private:
		void RecalculateProjection();
	private:
		CameraProjectionType m_CameraType = CameraProjectionType::Orthographic;

		float m_OrthoSize = 5.0f;
		float m_OrthoNear = -1.0f;
		float m_OrthoFar = 1.0f;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f;
		float m_PerspectiveFar = 1000.0f;

		float m_AspectRatio = 1.777777777777778f;
	};
}
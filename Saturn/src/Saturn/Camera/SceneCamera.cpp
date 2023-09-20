#include "SaturnPch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Saturn
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	SceneCamera::~SceneCamera() = default;

	void SceneCamera::SetOrtho(float size, float zNear, float zFar)
	{
		SetCameraProjectionType(CameraProjectionType::Orthographic);
		m_OrthoSize = size;
		m_OrthoNear = zNear;
		m_OrthoFar = zFar;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float vFov, float zNear, float zFar)
	{
		SetCameraProjectionType(CameraProjectionType::Perspective);
		m_PerspectiveFOV = vFov;
		m_PerspectiveNear = zNear;
		m_PerspectiveFar = zFar;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(UInt32 width, UInt32 height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_CameraType == CameraProjectionType::Orthographic)
		{
			float orthoLeft = -m_OrthoSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthoSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthoSize * 0.5f;
			float orthoTop = m_OrthoSize * 0.5f;

			m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthoNear, m_OrthoFar);
		} 
		else if (m_CameraType == CameraProjectionType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	}
}
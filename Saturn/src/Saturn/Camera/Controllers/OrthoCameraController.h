#pragma once
#include "Saturn/Events/ApplicationEvent.h"
#include "Saturn/Camera/OrthoCamera.h"
#include "Saturn/Events/MouseEvent.h"
#include "Saturn/Events/Event.h"
#include "Saturn/Core/Time.h"
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Saturn
{
	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation);

		void OnUpdate(Time time);
		void OnEvent(Event& e);

		inline const OrthoCamera& GetCamera() const
		{
			return m_OrthoCamera;
		}

		inline OrthoCamera& GetCamera()
		{
			return m_OrthoCamera;
		}

		inline void SetAspectRation(float v)
		{
			m_AspectRatio = v;
		}

		inline float GetAspectRation()
		{
			return m_AspectRatio;
		}
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_MinZoomLevel = 0.2f;
		float m_MaxZoomLevel = 7.0f;
		OrthoCamera m_OrthoCamera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		float m_CameraRotation = 0.0f;

		float m_CameraMoveSpeed = 3.0f;
		float m_CameraRotationSpeed = (float)M_PI;
	};
}
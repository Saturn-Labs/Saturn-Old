#include "SaturnPch.h"
#include "Saturn/Camera/Controllers/OrthoCameraController.h"
#include "Saturn/Input/Input.h"

namespace Saturn
{
	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_OrthoCamera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthoCameraController::OnUpdate(Time time)
	{
		if (Input::GetKeyCurrentState(KeyCode::A) == InputState::Down)
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * time;
		}
		else if (Input::GetKeyCurrentState(KeyCode::D) == InputState::Down)
		{
			m_CameraPosition.x += m_CameraMoveSpeed * time;
		}

		if (Input::GetKeyCurrentState(KeyCode::W) == InputState::Down)
		{
			m_CameraPosition.y += m_CameraMoveSpeed * time;
		}
		else if (Input::GetKeyCurrentState(KeyCode::S) == InputState::Down)
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * time;
		}

		if (m_Rotation)
		{
			if (Input::GetKeyCurrentState(KeyCode::Z) == InputState::Down)
			{
				m_CameraRotation -= m_CameraRotationSpeed * time;
			}
			else if (Input::GetKeyCurrentState(KeyCode::X) == InputState::Down)
			{
				m_CameraRotation += m_CameraRotationSpeed * time;
			}
			m_OrthoCamera.SetRotation(m_CameraRotation);
		}

		m_OrthoCamera.SetPosition(m_CameraPosition);
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(ST_BIND_EVENTFN(&OrthoCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ST_BIND_EVENTFN(&OrthoCameraController::OnWindowResized));
	}

	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() / 5;
		m_ZoomLevel = std::max(m_ZoomLevel, m_MinZoomLevel);

		m_OrthoCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_OrthoCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
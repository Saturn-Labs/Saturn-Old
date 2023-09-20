#pragma once
#include "ScriptableBehaviour.h"

#include "Saturn/Scene/Components/Transform.h"
#include "Saturn/Input/Input.h"

namespace Saturn
{
	class CameraBehaviour : public ScriptableBehaviour
	{
		Component::Transform* m_CameraTransform = nullptr;
		Component::CameraComponent* m_CameraComponent = nullptr;

		float m_CameraSpeed = 5.0f;
		float m_OrthoSizeMult = 15.0f;
		float m_OrthoSize = 3.0f;

		virtual void OnCreate() override
		{
			m_CameraTransform = &GetComponent<Component::Transform>();
			m_CameraComponent = &GetComponent<Component::CameraComponent>();
		}

		virtual void OnUpdate(Time time) override
		{
			if (m_CameraTransform)
			{
				if (Input::GetKeyCurrentState(KeyCode::A) == InputState::Down)
					m_CameraTransform->Position.x -= m_CameraSpeed * time;
				if (Input::GetKeyCurrentState(KeyCode::D) == InputState::Down)
					m_CameraTransform->Position.x += m_CameraSpeed * time;
				if (Input::GetKeyCurrentState(KeyCode::W) == InputState::Down)
					m_CameraTransform->Position.y += m_CameraSpeed * time;
				if (Input::GetKeyCurrentState(KeyCode::S) == InputState::Down)
					m_CameraTransform->Position.y -= m_CameraSpeed * time;
			}
		}

		virtual void OnDestroy() override
		{
			
		}
	};
}
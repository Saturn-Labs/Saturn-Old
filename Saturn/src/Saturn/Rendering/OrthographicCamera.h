#pragma once
#include "glm/glm.hpp"

namespace Saturn
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

		inline void SetPosition(glm::vec3 position)
		{
			m_Position = position;
			RecalculateViewMatrix();
		}

		inline void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		inline const glm::vec3& GetPosition() const
		{
			return m_Position;
		}

		inline float GetRotation() const
		{
			return m_Rotation;
		}

		inline const glm::mat4& GetProjectionMatrix() const
		{
			return m_Projection;
		}

		inline const glm::mat4& GetViewMatrix() const
		{
			return m_View;
		}

		inline const glm::mat4& GetViewProjectionMatrix() const
		{
			return m_ViewProjection;
		}
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_ViewProjection = glm::mat4(1.0f);

		glm::vec3 m_Position = glm::vec3();
		float m_Rotation = 0.0f;
	};
}
#pragma once
#include "glm/glm.hpp"
#include "Saturn/Debug/Instrumentor.h"

namespace Saturn
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);
		void SetProjection(float left, float right, float bottom, float top);

		inline void SetPosition(glm::vec3 position)
		{
			ST_PROFILE_FUNCTION();

			m_Position = position;
			RecalculateViewMatrix();
		}

		//IN RADIANS PLEASE
		inline void SetRotation(float rotation)
		{
			ST_PROFILE_FUNCTION();

			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		inline const glm::vec3& GetPosition() const
		{
			return m_Position;
		}

		//IN RADIANS
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
			ST_PROFILE_FUNCTION();

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
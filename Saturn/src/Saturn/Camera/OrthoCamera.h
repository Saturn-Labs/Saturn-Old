#pragma once
#include "glm/glm.hpp"
#include "Saturn/Debug/Instrumentor.h"

namespace Saturn
{
	class OrthoCamera
	{
	public:
		glm::vec3 Position = glm::vec3();
		float Rotation = 0.0f;

		OrthoCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);
		void SetProjection(float left, float right, float bottom, float top);

		inline void SetPosition(glm::vec3 position)
		{
			ST_PROFILE_FUNCTION();

			Position = position;
		}
		//IN RADIANS PLEASE
		inline void SetRotation(float rotation)
		{
			ST_PROFILE_FUNCTION();

			Rotation = rotation;
		}

		inline const glm::vec3& GetPosition() const
		{
			return Position;
		}
		//IN RADIANS
		inline float GetRotation() const
		{
			return Rotation;
		}

		inline const glm::mat4& GetProjectionMatrix() const
		{
			return m_Projection;
		}

	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Saturn/Debug/Instrumentor.h"

namespace Saturn
{
	struct TransformationMatrix
	{
		glm::vec3 Position = glm::vec3(0.0f);

		//IN RADIANS PLEASE
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		operator glm::mat4() const {
			ST_PROFILE_FUNCTION();
			glm::mat4 transformation = glm::mat4(1.0f);
			transformation = glm::translate(transformation, Position) *
				glm::rotate(transformation, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(transformation, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(transformation, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(transformation, Scale);
			return transformation;
		}

		glm::mat4 GetTransformation() const
		{
			return *this;
		}
	};
}
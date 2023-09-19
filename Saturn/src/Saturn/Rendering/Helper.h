#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/normal.hpp>

namespace Saturn
{
	class Helper
	{
	public:
		inline static glm::vec3 CalculateNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C)
		{
			return glm::triangleNormal(A, B, C);
		}
	};
}
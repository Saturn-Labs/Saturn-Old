#include "SaturnPch.h"
#include "Saturn/Camera/OrthoCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Saturn
{
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: m_Projection(glm::ortho(left, right, bottom, top, zNear, zFar))
	{
		
	}


	void OrthoCamera::SetProjection(float left, float right, float bottom, float top)
	{
		ST_PROFILE_FUNCTION();

		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
}
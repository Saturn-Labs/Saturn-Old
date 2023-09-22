#pragma once
#include "Types.h"
#include <glm/gtx/matrix_decompose.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Saturn
{
	struct Rect2D
	{
		Single x = 0.0f;
		Single y = 0.0f;
		Single width = 0.0f;
		Single height = 0.0f;
	};

	struct Rect2DInt
	{
		Int32 x = 0;
		Int32 y = 0;
		Int32 width = 0;
		Int32 height = 0;
	};

	struct UV
	{
		Single u = 0.0f;
		Single v = 0.0f;
	};

	class Math
	{
	public:
		inline static Single Normalize(UInt32 value, Int32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Int32 value, UInt32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Int32 value, Int32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(UInt32 value, UInt32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Single value, Single max)
		{
			return (value / max);
		}
		inline static Single Normalize(Single value, Int32 max)
		{
			return (value / max);
		}
		inline static Single Normalize(Single value, UInt32 max)
		{
			return (value / max);
		}

		inline static Vector3 ToRadians(const Vector3& degreesVector)
		{
			return degreesVector * (float)M_PI / 180.0f;
		}

		inline static Vector3 ToDegrees(const Vector3& radiansVector)
		{
			return radiansVector * 180.0f / (float)M_PI;
		}

		static bool DecomposeTransform(const Matrix4x4& transform, Vector3& outPos, Vector3& outRot, Vector3& outScale)
		{
			// From glm::decompose in matrix_decompose.inl

			using namespace glm;
			using T = float;

			mat4 LocalMatrix(transform);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
				return false;

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			outPos = vec3(LocalMatrix[3]);
			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3], Pdum3;

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			// Compute X scale factor and normalize first row.
			outScale.x = length(Row[0]);
			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			outScale.y = length(Row[1]);
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			outScale.z = length(Row[2]);
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
			#if 0
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					scale[i] *= static_cast<T>(-1);
					Row[i] *= static_cast<T>(-1);
				}
			}
			#endif

			outRot.y = asin(-Row[0][2]);
			if (cos(outRot.y) != 0)
			{
				outRot.x = atan2(Row[1][2], Row[2][2]);
				outRot.z = atan2(Row[0][1], Row[0][0]);
			}
			else
			{
				outRot.x = atan2(-Row[2][0], Row[1][1]);
				outRot.z = 0;
			}


			return true;
		}
	};
}
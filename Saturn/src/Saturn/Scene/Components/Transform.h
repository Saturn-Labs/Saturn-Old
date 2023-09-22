#pragma once
#include "Saturn/Common/Types.h"
#include "Saturn/Common/Math.h"

namespace Saturn::Component
{
	struct Transform
	{
		inline static Matrix4x4 Identity = Matrix4x4(1.0f);

		Transform()
		{
			RecalculateMatrix();
		};
		Transform(const Transform&) = default;
		Transform(const Vector3& translation, const Vector3& rotation, const Vector3& scale)
			: m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
		{
			RecalculateMatrix();
		}

		void SetTranslation(const Vector3& translation)
		{
			m_Translation = translation;
			RecalculateMatrix();
		}
		//Yall, Pitch and Roll - Radians please, if you want, you can use Saturn::Math::ToRadians.
		void SetEulerAngles(const Vector3& eulerAngles)
		{
			m_Rotation = eulerAngles;
			RecalculateMatrix();
		}
		void SetScale(const Vector3& scale)
		{
			m_Scale = scale;
			RecalculateMatrix();
		}

		Vector3 GetTranslation() const
		{
			return m_Translation;
		}
		//Yall, Pitch and Roll - In radians, if you want, you can use Saturn::Math::ToDegrees.
		Vector3 GetEulerAngles() const
		{
			return m_Rotation;
		}
		Vector3 GetScale() const
		{
			return m_Scale;
		}

		void RecalculateMatrix()
		{
			m_Matrix = glm::translate(Identity, m_Translation) *
				glm::rotate(Identity, m_Rotation.x, Vector3(1, 0, 0)) *
				glm::rotate(Identity, m_Rotation.y, Vector3(0, 1, 0)) *
				glm::rotate(Identity, m_Rotation.z, Vector3(0, 0, 1)) *
				glm::scale(Identity, m_Scale);


			m_InverseMatrix = glm::inverse(m_Matrix);
		}

		inline Matrix4x4& GetMatrix()
		{
			return m_Matrix;
		}
		inline Matrix4x4& GetInverseMatrix()
		{
			return m_InverseMatrix;
		}
		inline const Matrix4x4& GetMatrix() const
		{
			return m_Matrix;
		}
		inline const Matrix4x4& GetInverseMatrix() const
		{
			return m_InverseMatrix;
		}
		inline void SetMatrix(const Matrix4x4& matrix)
		{
			m_Matrix = matrix;
			m_InverseMatrix = glm::inverse(matrix);

			Math::DecomposeTransform(m_Matrix, m_Translation, m_Rotation, m_Scale);
		}
	private:
		Matrix4x4 m_Matrix = Identity;
		Matrix4x4 m_InverseMatrix = Identity;
		Vector3 m_Translation = Vector3(0.0f);
		Vector3 m_Rotation = Vector3(0.0f);
		Vector3 m_Scale = Vector3(1.0f);
	};
}
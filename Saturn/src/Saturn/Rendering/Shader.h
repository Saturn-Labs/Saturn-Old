#pragma once
#include <string>
#include "Saturn/Core.h"

namespace Saturn
{
	class Shader
	{
	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);
		~Shader();

		void Use();
		inline bool IsValid() const
		{
			return m_Id != -1;
		}

		static UInt32 CompileShaderProgram(const std::string& vertex, const std::string& fragment);
	private:
		UInt32 m_Id = 0;
	};
}
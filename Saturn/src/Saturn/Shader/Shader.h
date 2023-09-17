#pragma once
#include "Saturn/Core/Core.h"
#include <glm/glm.hpp>
#include <string>

namespace Saturn
{
	class Shader
	{
	public:
		Shader(const std::string& name);
		virtual ~Shader() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual Int32 GetUniformLocation(const std::string& name) = 0;

		virtual void UploadUniformFloat(const std::string& name, float value) const = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2 vec2) const = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3 vec3) const = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4 vec4) const = 0;

		virtual void UploadUniformInt(const std::string& name, int value) const = 0;
		virtual void UploadUniformInt2(const std::string& name, const glm::vec2 vec2) const = 0;
		virtual void UploadUniformInt3(const std::string& name, const glm::vec3 vec3) const = 0;
		virtual void UploadUniformInt4(const std::string& name, const glm::vec4 vec4) const = 0;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& mat3) const = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& mat4) const = 0;

		inline const std::string& GetName() const
		{
			return m_Name;
		}
	public:
		static Ref<Shader> Create(const std::string& sshaderFile);
		static Ref<Shader> Create(const std::string& name, const std::string& sshaderSrc);

	private:
		std::string m_Name;
	};
}
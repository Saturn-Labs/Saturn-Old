#pragma once
#include "Saturn/Shader/Shader.h"
#include <glm/glm.hpp>

namespace Saturn
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& sshaderFile);
		OpenGLShader(const std::string& name, const std::string& sshaderSrc);

		virtual ~OpenGLShader();
		virtual void Bind() override final;
		virtual void Unbind() override final;

		virtual Int32 GetUniformLocation(const std::string& name) override;

		virtual void UploadUniformFloat(const std::string& name, float value) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2 vec2) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3 vec3) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4 vec4) override;

		virtual void UploadUniformInt(const std::string& name, int value) override;
		virtual void UploadUniformInt2(const std::string& name, const glm::vec2 vec2) override;
		virtual void UploadUniformInt3(const std::string& name, const glm::vec3 vec3) override;
		virtual void UploadUniformInt4(const std::string& name, const glm::vec4 vec4) override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& mat3) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& mat4) override;

		static UInt32 CompileOpenGLShaderProgram(const std::string& vertex, const std::string& fragment);
	private:
		UInt32 m_Id;
		std::unordered_map<std::string, Int32> m_UniformLocationCache;
	};
}
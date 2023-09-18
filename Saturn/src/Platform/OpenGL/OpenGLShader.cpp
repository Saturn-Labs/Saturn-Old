#include "SaturnPch.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Saturn/Shader/ShaderPreprocessor.h"
#include "Saturn/Core/Core.h"
#include "Saturn/IO/Log.h"
#include "Saturn/IO/IO.h"

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Saturn
{
	OpenGLShader::OpenGLShader(const std::string& sshaderFile)
		: Shader(std::filesystem::path(sshaderFile).stem().string())
	{
		ST_PROFILE_FUNCTION();
		ShaderData data = ShaderPreprocessor::Preprocess(IO::File::ReadAllText(sshaderFile));
		if (data.valid)
		{
			m_Id = OpenGLShader::CompileOpenGLShaderProgram(data.vertex, data.fragment);
		}
		else
			m_Id = -1;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& src)
		: Shader(name)
	{
		ST_PROFILE_FUNCTION();
		ShaderData data = ShaderPreprocessor::Preprocess(src);
		if (data.valid)
		{
			m_Id = OpenGLShader::CompileOpenGLShaderProgram(data.vertex, data.fragment);
		}
		else
			m_Id = -1;
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_Id);
	}

	void OpenGLShader::Bind()
	{
		ST_PROFILE_FUNCTION();
		glUseProgram(m_Id);
	}
	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	Int32 OpenGLShader::GetUniformLocation(const std::string& name)
	{
		ST_PROFILE_FUNCTION();

		if (m_UniformLocationCache.find(name) == m_UniformLocationCache.end())
		{
			Int32 location = glGetUniformLocation(m_Id, name.c_str());
			if (location == -1)
			{
				ST_CORE_WARN("[{0}] Trying to get location of a invalid uniform \"{1}\"", __FUNCTION__, name);
				return -1;
			}
			m_UniformLocationCache[name] = location;
			return location;
		}
		return m_UniformLocationCache[name];
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform1f(uniformLocation, value);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2 vec2)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform2f(uniformLocation, vec2.x, vec2.y);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3 vec3)
	{
		ST_PROFILE_FUNCTION();

		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform3f(uniformLocation, vec3.x, vec3.y, vec3.z);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4 vec4)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform4f(uniformLocation, vec4.x, vec4.y, vec4.z, vec4.w);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		ST_PROFILE_FUNCTION();

		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform1i(uniformLocation, value);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::vec2 vec2)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform2i(uniformLocation, (int)vec2.x, (int)vec2.y);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::vec3 vec3)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform3i(uniformLocation, (int)vec3.x, (int)vec3.y, (int)vec3.z);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::vec4 vec4)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniform4i(uniformLocation, (int)vec4.x, (int)vec4.y, (int)vec4.z, (int)vec4.w);
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& mat3)
	{
		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat3));
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& mat4)
	{
		ST_PROFILE_FUNCTION();

		Int32 uniformLocation = GetUniformLocation(name);
		if (uniformLocation != -1)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
		else
			ST_CORE_WARN("[{0}] Trying to use a invalid uniform location \"{1}\"", __FUNCTION__, name);
	}

	UInt32 OpenGLShader::CompileOpenGLShaderProgram(const std::string& vertex, const std::string& fragment)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = (const GLchar*)vertex.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[OpenGL shader compilation error (VERTEX)]: {0}", infoLog.data());
			glDeleteShader(vertexShader);
			return -1;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*)fragment.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[OpenGL shader compilation error (FRAGMENT)]: {0}", infoLog.data());
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			return -1;
		}

		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[OpenGL shader program linking error]: {0}", infoLog.data());
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return -1;
		}
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		return program;
	}
}

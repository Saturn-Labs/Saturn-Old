#include "saturnpch.h"
#include "Shader.h"
#include "Saturn/IO/IO.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Saturn
{
	Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	{
		std::string vertex = IO::File::ReadAllText(vertexFile);
		std::string fragment = IO::File::ReadAllText(fragmentFile);

		m_Id = Shader::CompileShaderProgram(vertex, fragment);
	}

	Shader::~Shader()
	{
		if (IsValid())
			glDeleteProgram(m_Id);
	}

	void Shader::Use()
	{
		if (IsValid())
			glUseProgram(m_Id);
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat4) const
	{
		Int32 uniformLocation = glGetUniformLocation(m_Id, name.c_str());
		if (uniformLocation != -1)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
		else
			ST_CORE_WARN("Trying to write on a invalid uniform \"{0}\" {1}", name, uniformLocation);
	}

	UInt32 Shader::CompileShaderProgram(const std::string& vertex, const std::string& fragment)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertex.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[Shader compilation error (VERTEX)] {0}", infoLog.data());

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return -1;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragment.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[Shader compilation error (FRAGMENT)] {0}", infoLog.data());

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return -1;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			ST_CORE_ERROR("[Shader program linking error] {0}", infoLog.data());

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			return -1;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		return program;
	}
}

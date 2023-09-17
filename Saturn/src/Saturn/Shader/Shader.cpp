#include "SaturnPch.h"
#include "Saturn/Rendering/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Saturn/Shader/Shader.h"

namespace Saturn
{
	Shader::Shader(const std::string& name)
		: m_Name(name)
	{
	}

	Ref<Shader> Shader::Create(const std::string& sshaderFile)
	{
		switch (RendererAPI::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<Shader>(new OpenGLShader(sshaderFile));
				break;
		}
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& sshaderSrc)
	{
		switch (RendererAPI::GetRendererAPI())
		{
			case RendererAPI::API::OpenGL:
				return Ref<Shader>(new OpenGLShader(name, sshaderSrc));
				break;
		}
		return nullptr;
	}
}

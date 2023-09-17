#include "saturnpch.h"
#include "ShaderLib.h"
#include "Saturn/Core.h"

namespace Saturn
{
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		ST_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists in ShaderLib!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		auto& name = shader->GetName();
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(name, filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) const
	{
		if (m_Shaders.find(name) == m_Shaders.end())
		{
			ST_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader not found in ShaderLib!");
			return nullptr;
		}
		else
			return m_Shaders.find(name)->second;
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
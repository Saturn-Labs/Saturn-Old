#pragma once
#include <string>

namespace Saturn
{
	struct ShaderData
	{
		std::string vertex;
		std::string fragment;
		const bool valid;
	};

	class ShaderProcessor
	{
	public:
		static ShaderData Preprocess(const std::string& baseIncPath, const std::string& sshader);
		static ShaderData PostProcess(const ShaderData& data);
	};
}
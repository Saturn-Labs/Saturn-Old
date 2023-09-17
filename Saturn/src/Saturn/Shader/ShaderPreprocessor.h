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

	class ShaderPreprocessor
	{
	public:
		static ShaderData Preprocess(const std::string& sshader);
	};
}
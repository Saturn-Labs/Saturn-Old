#include "saturnpch.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>

#include "ShaderPreprocessor.h"

namespace Saturn
{
	ShaderData ShaderPreprocessor::Preprocess(const std::string& sshader)
	{
		if (!sshader.empty())
		{
			std::string version = "#version ";

			std::string parsedVert;
			std::string parsedFrag;

			std::istringstream srcstr(sshader);
			std::string line;

			bool inProgramBlock = false;
			bool findedProgram = false;

			bool inVertexBlock = false;
			bool inFragmentBlock = false;

			bool findedVersion = false;

			bool findedVertex = false;
			bool findedFragment = false;

			int lineIndex = -1;
			while (std::getline(srcstr, line))
			{
				lineIndex++;
				if (line.find(":program") != line.npos)
				{
					if (!inProgramBlock || (inVertexBlock || inFragmentBlock))
					{
						ST_CORE_ERROR("[Shader preprocessor error] Unexpected end of 'program' block, in line: ({0})",
							lineIndex);
						return { "", "", false };
					}

					inProgramBlock = false;
				}

				if (inProgramBlock)
				{
					size_t verOffset = 0;
					if (verOffset = line.find("version:") != line.npos)
					{
						size_t verDtOff = verOffset + 7;
						verDtOff = line.find("\"");
						verDtOff++;

						while (line[verDtOff] != '\"')
						{
							version += line[verDtOff];
							verDtOff++;
						}

						findedVersion = true;
						parsedVert += version + "\n";
						parsedFrag += version + "\n";
					}

					size_t globOffset = 0;
					if (globOffset = line.find("global:") != line.npos)
					{
						size_t globDtOff = globOffset + 6;
						globDtOff = line.find("\"");
						globDtOff++;

						std::string globalData;
						while (line[globDtOff] != '\"')
						{
							globalData += line[globDtOff];
							globDtOff++;
						}

						parsedVert += globalData + "\n";
						parsedFrag += globalData + "\n";
					}

					if (line.find(":vertex") != line.npos)
					{
						if (!inVertexBlock || inFragmentBlock)
						{
							ST_CORE_ERROR("[Shader preprocessor error] Unexpected end of 'vertex' block, in line: ({0})",
								lineIndex);
							return { "", "", false };
						}
						inVertexBlock = false;
					}
					if (line.find(":fragment") != line.npos)
					{
						if (!inFragmentBlock || inVertexBlock)
						{
							ST_CORE_ERROR("[Shader preprocessor error] Unexpected end of 'fragment' block, in line: ({0})",
								lineIndex);
							return { "", "", false };
						}
						inFragmentBlock = false;
					}

					if (inVertexBlock)
					{
						parsedVert += line + "\n";
					}
					if (inFragmentBlock)
					{
						parsedFrag += line + "\n";
					}

					if (line.find("vertex:") != line.npos)
					{
						if (inVertexBlock || inFragmentBlock)
						{
							ST_CORE_ERROR("[Shader preprocessor error] Unexpected start of 'vertex' block, in line: ({0})",
								lineIndex);
							return { "", "", false };
						}
						inVertexBlock = true;
						findedVertex = true;
						parsedVert += "#define vert main\n";
					}
					if (line.find("fragment:") != line.npos)
					{
						if (inFragmentBlock || inVertexBlock)
						{
							ST_CORE_ERROR("[Shader preprocessor error] Unexpected start of 'fragment' block, in line: ({0})",
								lineIndex);
							return { "", "", false };
						}
						inFragmentBlock = true;
						findedFragment = true;
						parsedFrag += "#define frag main\n";
					}
				}

				if (line.find("program:") != line.npos)
				{
					if (inProgramBlock)
					{
						ST_CORE_ERROR("[Shader preprocessor error] Unexpected start of 'program' block, in line: ({0})",
							lineIndex);
						return { "", "", false };
					}

					inProgramBlock = true;
					findedProgram = true;
				}
			}

			if (findedVersion && findedProgram && findedVertex && findedFragment)
				return { parsedVert, parsedFrag, true };
			else
				ST_CORE_ERROR("[Shader preprocessor error] One or more headers missing!");
		}
		return { "", "", false };
	}
}
#include "SaturnPch.h"
#include "Saturn/Shader/ShaderPreprocessor.h"
#include "Saturn/IO/IO.h"

namespace Saturn
{
	ShaderData ShaderPreprocessor::Preprocess(const std::string& baseIncPath, const std::string& sshader)
	{
		ST_PROFILE_FUNCTION();
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

					size_t incOffset = 0;
					if (incOffset = line.find("includefile:") != line.npos)
					{
						size_t incDtOff = incOffset + 11;
						incDtOff = line.find("\"");
						incDtOff++;

						std::string incPath;
						while (line[incDtOff] != '\"')
						{
							incPath += line[incDtOff];
							incDtOff++;
						}

						//parsedVert += incPath + "\n";
						//parsedFrag += incPath + "\n";

						std::string filePath = (std::filesystem::path(baseIncPath) / std::filesystem::path(incPath)).string();
						if (!IO::File::Exists(filePath))
						{
							ST_CORE_ERROR("[Saturn shader preprocessor] Invalid shader include path: \"{0}\" not found!\nComplete path: \"{1}\"", incPath, filePath);
						}
						else
						{
							std::string includeContent = IO::File::ReadAllText(filePath);

							if (inVertexBlock)
							{
								parsedVert += "//included from \"" + incPath + "\"\n";
								parsedVert += includeContent + "\n";
							}

							if (inFragmentBlock)
							{
								parsedFrag += "//included from \"" + incPath + "\"\n";
								parsedFrag += includeContent + "\n";
							}
						}

						line = "\n";
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
						parsedVert += "#define Vertex_Out_Position gl_Position\n";
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
						parsedFrag += "#define Fragment_Out_Color FragOutColor\n";
						parsedFrag += "layout(location = 0) out vec4 FragOutColor;\n";
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
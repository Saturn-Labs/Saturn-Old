#include "SaturnPch.h"
#include "Saturn/IO/IO.h"

namespace Saturn::IO
{
	bool File::Exists(const std::string& path)
	{
		if (FILE* file = fopen(path.c_str(), "r"))
		{
			fclose(file);
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string File::ReadAllText(const std::string& path)
	{
		if (!File::Exists(path))
		{
			ST_CORE_ERROR("[Saturn::IO Exception] Trying to read all text from a non-existent file \"{0}\"", path);
		}
		else
		{
			std::ifstream file(path);
			if (file.is_open())
			{
				std::stringstream string;
				std::string line;
				while (std::getline(file, line))
				{
					string << line << "\n";
				}
				return string.str();
			}
		}
		return {};
	}

	std::vector<std::string> File::ReadAllLines(const std::string& path)
	{
		if (!File::Exists(path))
		{
			ST_CORE_ERROR("[Saturn::IO Exception] Trying to read all text from a non-existent file \"{0}\"", path);
		}
		else
		{
			std::ifstream file(path);
			if (file.is_open())
			{
				std::vector<std::string> lines;
				std::string line;
				while (std::getline(file, line))
				{
					lines.push_back(line);
				}
				return lines;
			}
		}
		return {};
	}
}

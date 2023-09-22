#pragma once
#include <string>

namespace Saturn
{
	class FileDialog
	{
	public:
		//Return empty standard::string if cancelled.
		static std::string OpenFile(const char* filter);

		//Return empty standard::string if cancelled.
		static std::string SaveFile(const char* filter);
	};
}
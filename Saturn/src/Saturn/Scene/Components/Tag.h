#pragma once
#include "Saturn/Common/Types.h"
#include <string>

namespace Saturn::Component
{
	struct Tag
	{
		std::string Name;

		Tag() = default;
		Tag(const Tag&) = default;

		Tag(const std::string& name)
			: Name(name) { }
	};
}
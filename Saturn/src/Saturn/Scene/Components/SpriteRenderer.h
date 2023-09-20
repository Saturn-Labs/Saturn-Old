#pragma once
#include "Saturn/Common/Types.h"

namespace Saturn::Component
{
	struct SpriteRenderer
	{
		Color Color = ::Color(1.0f);

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const ::Color& color) 
			: Color(color) { }
	};
}
#pragma once
#include "Types.h"

namespace Saturn
{
	struct Rect2D
	{
		Single x = 0.0f;
		Single y = 0.0f;
		Single width = 0.0f;
		Single height = 0.0f;
	};

	struct Rect2DInt
	{
		Int32 x = 0;
		Int32 y = 0;
		Int32 width = 0;
		Int32 height = 0;
	};

	struct UV
	{
		Single u = 0.0f;
		Single v = 0.0f;
	};

	class Math
	{
	public:
		inline static Single Normalize(UInt32 value, Int32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Int32 value, UInt32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Int32 value, Int32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(UInt32 value, UInt32 max)
		{
			return Math::Normalize((Single)value, (Single)max);
		}
		inline static Single Normalize(Single value, Single max)
		{
			return (value / max);
		}
		inline static Single Normalize(Single value, Int32 max)
		{
			return (value / max);
		}
		inline static Single Normalize(Single value, UInt32 max)
		{
			return (value / max);
		}
	};
}
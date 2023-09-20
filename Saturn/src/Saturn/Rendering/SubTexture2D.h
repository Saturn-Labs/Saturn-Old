#pragma once
#include "Saturn/Core/Core.h"
#include "Saturn/Rendering/Texture2D.h"
#include "Saturn/Common/Math.h"

#include <array>

namespace Saturn
{

	class SubTexture2D
	{
	public:
		SubTexture2D(Ref<Texture2D> texture, const Rect2DInt& rect);
		SubTexture2D(Ref<Texture2D> texture, const glm::vec2& maxTiles, const glm::vec2& subPos, const glm::vec2& subSize);

		inline Ref<Texture2D> GetTexture2D() const
		{
			return m_Texture2D;
		}

		inline const Rect2DInt& GetRect2D() const
		{
			return m_Region;
		}

		inline const UV& GetUV(Int32 index) const
		{
			ST_CORE_ASSERT(!(index > 3), "[Saturn SubTexture2D] Index out of range trying to access the UV of a subtexture!");
			return m_TextureCoords[index];
		}

		inline const UV& operator[](Int32 index)
		{
			return GetUV(index);
		}
	private:
		Rect2DInt m_Region;
		std::array<UV, 4> m_TextureCoords;
		Ref<Texture2D> m_Texture2D;
	};
}
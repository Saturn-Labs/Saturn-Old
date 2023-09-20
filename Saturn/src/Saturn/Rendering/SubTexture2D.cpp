#include "SaturnPch.h"
#include "Saturn/Rendering/SubTexture2D.h"

namespace Saturn
{
	SubTexture2D::SubTexture2D(Ref<Texture2D> texture, const Rect2DInt& rect)
	{
		ST_CORE_ASSERT(texture, "[Saturn SubTexture2D] Trying to pass a nullptr texture into the subtexture!");

		m_Texture2D = texture;
		m_Region = rect;

		UInt32 texWidth = texture->GetWidth();
		UInt32 texHeight = texture->GetHeight();

		Single normX = Math::Normalize(rect.x, texWidth);
		Single normY = Math::Normalize(rect.y, texHeight);
		Single normWidth = Math::Normalize(rect.width, texWidth);
		Single normHeight = Math::Normalize(rect.height, texHeight);

		m_TextureCoords[0] = { normX, normY };
		m_TextureCoords[1] = { normWidth + normX, normY };
		m_TextureCoords[2] = { normWidth + normX, (normHeight + normY) };
		m_TextureCoords[3] = { normX, (normHeight + normY) };
	}

	SubTexture2D::SubTexture2D(Ref<Texture2D> texture, const glm::vec2& maxTiles, const glm::vec2& subPos, const glm::vec2& subSize)
	{
		ST_CORE_ASSERT(texture, "[Saturn SubTexture2D] Trying to pass a nullptr texture into the subtexture!");

		m_Texture2D = texture;

		glm::vec2 tileSize = { (m_Texture2D->GetWidth() / maxTiles.x), (m_Texture2D->GetHeight() / maxTiles.y) };

		ST_CORE_TRACE("Sub X {0}", subPos.x);
		ST_CORE_TRACE("Sub Y {0}", subPos.y);

		ST_CORE_TRACE("Sub Size X {0}", subSize.x);
		ST_CORE_TRACE("Sub Size Y {0}", subSize.y);

		glm::vec2 fullPos = subPos * tileSize;
		fullPos -= tileSize;

		ST_CORE_TRACE("Full X {0}", fullPos.x);
		ST_CORE_TRACE("Full Y {0}", fullPos.y);

		m_Region = { (Int32)fullPos.x, (Int32)fullPos.y, (Int32)subSize.x, (Int32)subSize.y };

		UInt32 texWidth = texture->GetWidth();
		UInt32 texHeight = texture->GetHeight();

		Single normX = Math::Normalize(fullPos.x, texWidth);
		Single normY = Math::Normalize(fullPos.y, texHeight);
		Single normWidth = Math::Normalize(subSize.x, texWidth);
		Single normHeight = Math::Normalize(subSize.y, texHeight);

		m_TextureCoords[0] = { normX, normY };
		m_TextureCoords[1] = { normWidth + normX, normY };
		m_TextureCoords[2] = { normWidth + normX, (normHeight + normY) };
		m_TextureCoords[3] = { normX, (normHeight + normY) };
	}
}
#pragma once
#include "Saturn/Common/Types.h"
#include "Saturn/Rendering/Tile2D.h"
#include <glm/glm.hpp>

namespace Saturn
{
	template<UInt32 W, UInt32 H>
	class Tilemap2D
	{
	public:
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(1.0f);
		glm::vec3 Scale = glm::vec3(0.0f);

		Tilemap2D()
		{
			for (UInt32 x = 0; x < W; x++)
			{
				for (UInt32 y = 0; y < H; y++)
				{
					m_Tiles[x][y] = nullptr;
				}
			}
		}

		Tilemap2D(Ref<Tile2D> tile)
		{
			for (UInt32 x = 0; x < W; x++)
			{
				for (UInt32 y = 0; y < H; y++)
				{
					m_Tiles[x][y] = tile;
				}
			}
		}

		void SetTile(const glm::ivec2& pos, const Ref<Tile2D>& tile)
		{
			m_Tiles[pos.x][pos.y] = tile;
		}

		void Draw() const
		{
			for (UInt32 x = 0; x < W; x++)
			{
				for (UInt32 y = 0; y < H; y++)
				{
					Ref<Tile2D> tile = m_Tiles[x][y];
					if (tile)
						Renderer2D::DrawQuad(glm::vec3(x + 4, y + 4, 0.0f) + tile->Offset + Position, Rotation, tile->Scale + Scale, tile->GetSubTexture(), tile->Color);
				}
			}
		}

		constexpr UInt32 GetTilemapSize() const
		{
			return W * H;
		}
	private:
		UInt32 m_Width = W;
		UInt32 m_Height = H;

		Ref<Tile2D> m_Tiles[W][H];
	};
}
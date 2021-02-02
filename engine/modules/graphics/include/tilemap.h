#pragma once
#include <vector>

#include <tile.h>
#include <vector.h>

namespace alloy::graphics {
class Tilemap {
public:
	//TODO Use a correct loading system for all tilesets
	Tilemap(const math::ivec2 nbTiles, const math::ivec2 tileSize) :
		nbTiles_(nbTiles),
		tileSize_(tileSize),
		tileSet_(TextureMode::TILESET, {4, 4}){ }

	void Init();

	void Draw(sf::RenderTarget& target) const;

	void UpdateChunk(const std::vector<Tile>& tiles, math::uivec2 topLeft, math::uivec2 bottomRight);

	const Texture& GetTileset() const {
		return tileSet_;
	}
	
private:
	math::ivec2 nbTiles_;
	math::ivec2 tileSize_;

	sf::VertexArray tilesVertexArray_;

	Texture tileSet_;

	const int vertexPerQuad_ = 4;
};
} //namespace alloy::graphics

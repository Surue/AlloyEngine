#pragma once
#include <vector>

#include <tile.h>
#include <vector.h>

namespace alloy::graphics {
class Tilemap {
public:
	//TODO stop using a given size and cut into chunk
	Tilemap(const math::ivec2 nbTiles, const math::ivec2 tileSize) :
		nbTiles_(nbTiles),
		tileSize_(tileSize),
		tileSet_(TextureMode::TILESET, {4, 4}){ }

	void Init();

	void Draw(sf::RenderTarget& target) const {
		sf::RenderStates renderStates;

		renderStates.transform = sf::Transform::Identity;
		renderStates.texture = &tileSet_.GetSfTexture();
		
		target.draw(tilesVertexArray_, renderStates);
	}

	void UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft, const math::uivec2 bottomRight) {
		int index = 0;
		for(int x = topLeft.x; x < bottomRight.x; x++) {
			for(int y = topLeft.y; y < bottomRight.y; y++){
				sf::Vertex* tileQuad = &tilesVertexArray_[(x + y * nbTiles_.x) * 4];

				const auto& texCoords = tiles[index].GetTextureCoordsInPixel();

				tileQuad[0].texCoords = sf::Vector2f(texCoords[0].x, texCoords[0].y);
				tileQuad[1].texCoords = sf::Vector2f(texCoords[1].x, texCoords[1].y);
				tileQuad[2].texCoords = sf::Vector2f(texCoords[2].x, texCoords[2].y);
				tileQuad[3].texCoords = sf::Vector2f(texCoords[3].x, texCoords[3].y);

				index++;
			}
		}
	}

	const Texture& GetTileset() const {
		return tileSet_;
	}
	
private:
	math::ivec2 nbTiles_;
	math::ivec2 tileSize_;

	sf::VertexArray tilesVertexArray_;

	Texture tileSet_;
};
} //namespace alloy::graphics

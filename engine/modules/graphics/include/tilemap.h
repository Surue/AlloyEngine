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

	void Init() {
		debug::Log("Init tilemap");

		tileSet_.Load("data/sprites/color_tileset.png");

		//TODO remove magic number => 4 is equal to the number of vertex for a quad
		tilesVertexArray_.setPrimitiveType(sf::Quads);
		tilesVertexArray_.resize(nbTiles_.x * nbTiles_.y * 4);
		
		for(int x = 0; x < nbTiles_.x; x++) {

			int offset = 0;
			if (x % 2 == 0) {
				offset = 1;
			}
			for(int y = 0; y < nbTiles_.y; y++) {
				//TODO remove magic number => 4 is equal to the number of vertex for a quad
				sf::Vertex* tileQuad = &tilesVertexArray_[(x + y * nbTiles_.x) * 4];

				//Set positions of every tiles
				tileQuad[0].position = sf::Vector2f(x * tileSize_.x, y * tileSize_.y);
				tileQuad[1].position = sf::Vector2f((x + 1) * tileSize_.x, y * tileSize_.y);
				tileQuad[2].position = sf::Vector2f((x + 1) * tileSize_.x, (y + 1) * tileSize_.y);
				tileQuad[3].position = sf::Vector2f(x * tileSize_.x, (y + 1) * tileSize_.y);

				//TODO remove magic number => 14 == number of tile in tileset
				const int textureIndex = (x + y * nbTiles_.x) % 14;


				auto texCoords = tileSet_.GetTextureCoordInPixel(textureIndex);

				tileQuad[0].texCoords = sf::Vector2f(texCoords[0].x, texCoords[0].y);
				tileQuad[1].texCoords = sf::Vector2f(texCoords[1].x, texCoords[1].y);
				tileQuad[2].texCoords = sf::Vector2f(texCoords[2].x, texCoords[2].y);
				tileQuad[3].texCoords = sf::Vector2f(texCoords[3].x, texCoords[3].y);
				
				//if((y + offset) % 2 == 0) {
				//	tileQuad[0].color = sf::Color::Red;
				//	tileQuad[1].color = sf::Color::Black;
				//	tileQuad[2].color = sf::Color::Black;
				//	tileQuad[3].color = sf::Color::Black;
				//}else {
				//	tileQuad[0].color = sf::Color::White;
				//	tileQuad[1].color = sf::Color::White;
				//	tileQuad[2].color = sf::Color::White;
				//	tileQuad[3].color = sf::Color::White;
				//}
			}
		}
		
		const math::uivec2 topLeft = { 1, 1 };
		const math::uivec2 bottomRight{ 5, 5 };

		const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
		Tile baseTile = Tile(tileSet_, 0);
		std::vector<Tile> tiles( nbTiles, baseTile);

		for(auto& tile : tiles) {
			tile.SetSprite(4);
		}

		UpdateChunk(tiles, topLeft, bottomRight);
	}

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
	
private:
	math::ivec2 nbTiles_;
	math::ivec2 tileSize_;

	sf::VertexArray tilesVertexArray_;

	Texture tileSet_;
};
} //namespace alloy::graphics

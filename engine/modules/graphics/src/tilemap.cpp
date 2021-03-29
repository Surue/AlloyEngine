#include <tilemap.h>

namespace alloy::graphics {

void Tilemap::Init() {
	tileSet_.Load("data/sprites/color_tileset.png");

	tilesVertexArray_.setPrimitiveType(sf::Quads);
	tilesVertexArray_.resize(static_cast<std::size_t>(nbTiles_.x) * static_cast<std::size_t>(nbTiles_.y) * vertexPerQuad_);

	for (int x = 0; x < nbTiles_.x; x++) {

		for (int y = 0; y < nbTiles_.y; y++) {
			sf::Vertex* tileQuad = &tilesVertexArray_[(x + y * nbTiles_.x) * vertexPerQuad_];

			//Set positions of every tiles
			tileQuad[0].position = sf::Vector2f(x * tileSize_.x, y * tileSize_.y);
			tileQuad[1].position = sf::Vector2f((x + 1) * tileSize_.x, y * tileSize_.y);
			tileQuad[2].position = sf::Vector2f((x + 1) * tileSize_.x, (y + 1) * tileSize_.y);
			tileQuad[3].position = sf::Vector2f(x * tileSize_.x, (y + 1) * tileSize_.y);

			//TODO 1.0 remove magic number => 14 == number of tile in tileset
			const int textureIndex = (x + y * nbTiles_.x) % 14;

			auto texCoords = tileSet_.GetTextureCoordInPixel(textureIndex);

			tileQuad[0].texCoords = sf::Vector2f(texCoords[0].x, texCoords[0].y);
			tileQuad[1].texCoords = sf::Vector2f(texCoords[1].x, texCoords[1].y);
			tileQuad[2].texCoords = sf::Vector2f(texCoords[2].x, texCoords[2].y);
			tileQuad[3].texCoords = sf::Vector2f(texCoords[3].x, texCoords[3].y);
		}
	}
}

void Tilemap::Draw(sf::RenderTarget& target) const {
	sf::RenderStates renderStates;

	renderStates.transform = sf::Transform::Identity;
	renderStates.texture = &tileSet_.GetSfTexture();

	target.draw(tilesVertexArray_, renderStates);
}

void Tilemap::UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft, const math::uivec2 bottomRight) {
	int index = 0;
	for (auto x = topLeft.x; x < bottomRight.x; x++) {
		for (auto y = topLeft.y; y < bottomRight.y; y++) {
			auto* tileQuad = &tilesVertexArray_[(x + y * nbTiles_.x) * vertexPerQuad_];

			const auto& texCoords = tiles[index].GetTextureCoordsInPixel();

			tileQuad[0].texCoords = sf::Vector2f(texCoords[0].x, texCoords[0].y);
			tileQuad[1].texCoords = sf::Vector2f(texCoords[1].x, texCoords[1].y);
			tileQuad[2].texCoords = sf::Vector2f(texCoords[2].x, texCoords[2].y);
			tileQuad[3].texCoords = sf::Vector2f(texCoords[3].x, texCoords[3].y);

			index++;
		}
	}
}
}

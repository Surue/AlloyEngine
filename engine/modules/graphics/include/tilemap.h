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
		tileSize_(tileSize) { }

	void Init() {
		debug::Log("Init tilemap");

		tileSet_.Load("data/sprites/policeman.png");

		//TODO remove magic number => 4 is equal to the number of vertex for a quad
		tilesVertexArray_.setPrimitiveType(sf::Quads);
		tilesVertexArray_.resize(nbTiles_.x * nbTiles_.y * 4);
		
		tiles_.resize(nbTiles_.x * nbTiles_.y);
		
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

				tileQuad[0].texCoords = sf::Vector2f(0, 0);
				tileQuad[1].texCoords = sf::Vector2f(505, 0);
				tileQuad[2].texCoords = sf::Vector2f(505, 505);
				tileQuad[3].texCoords = sf::Vector2f(0, 505);
				
				if((y + offset) % 2 == 0) {
					tileQuad[0].color = sf::Color::Red;
					tileQuad[1].color = sf::Color::Black;
					tileQuad[2].color = sf::Color::Black;
					tileQuad[3].color = sf::Color::Black;
				}else {
					tileQuad[0].color = sf::Color::White;
					tileQuad[1].color = sf::Color::White;
					tileQuad[2].color = sf::Color::White;
					tileQuad[3].color = sf::Color::White;
				}
			}
		}
	}

	void Draw(sf::RenderTarget& target) const {
		sf::RenderStates renderStates;

		renderStates.transform = sf::Transform::Identity;
		renderStates.texture = &tileSet_.GetSfTexture();
		
		target.draw(tilesVertexArray_, renderStates);
	}
	
private:
	math::ivec2 nbTiles_;
	math::ivec2 tileSize_;

	std::vector<Tile> tiles_;
	sf::VertexArray tilesVertexArray_;

	Texture tileSet_;
};
} //namespace alloy::graphics

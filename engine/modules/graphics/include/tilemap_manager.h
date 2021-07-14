#pragma once
#include <service_locator.h>

#include <tilemap.h>

namespace alloy::graphics {
using TilemapIndex = int;

class TilemapManager : public IService{
public:
	TilemapManager() { 
		
	}

	void Init();

	Tilemap& GetTilemap(TilemapIndex tilemapIndex);

	void Draw(sf::RenderTarget& target) const;

	TilemapIndex CreateTilemap(const math::ivec2 nbTiles, const math::ivec2 tileSize) {
		const TilemapIndex index = tilemapCount_;
		tilemaps_.push_back(Tilemap(nbTiles, tileSize));

		tilemaps_[index].Init();

		tilemapCount_++;
		return index;
	}
private:
	std::vector<Tilemap> tilemaps_;
	int tilemapCount_ = 0;
};
}

#include <tilemap_manager.h>

namespace alloy::graphics {

void TilemapManager::Init() {
	
}

Tilemap& TilemapManager::GetTilemap(const TilemapIndex tilemapIndex) {
	return tilemaps_[tilemapIndex];
}

void TilemapManager::Draw(sf::RenderTarget& target) const {
	for(size_t i = 0; i < tilemaps_.size(); i++) {
		tilemaps_[i].Draw(target);
	}
}
}

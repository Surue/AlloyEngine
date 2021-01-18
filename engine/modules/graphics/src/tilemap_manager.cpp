#include <tilemap_manager.h>

namespace alloy::graphics {

void TilemapManager::Init() {
	tilemap_.Init();
}

const Tilemap& TilemapManager::GetTilemap() const {
	return tilemap_;
}

void TilemapManager::UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft,
                                 const math::uivec2 bottomRight) {
	tilemap_.UpdateChunk(tiles, topLeft, bottomRight);
}

void TilemapManager::Draw(sf::RenderTarget& target) const {
	tilemap_.Draw(target);
}
}

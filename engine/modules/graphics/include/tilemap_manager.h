#pragma once
#include <service_locator.h>

#include <tilemap.h>

namespace alloy::graphics {
class TilemapManagerBase {
public:
	virtual void Init() = 0;
	
	virtual const Tilemap& GetTilemap() const = 0;

	virtual void UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft, const math::uivec2 bottomRight) = 0;

	virtual void Draw(sf::RenderTarget& target) const = 0;
};

class TilemapManagerNull : public TilemapManagerBase{
public:
	void Init() override{}
	
	const Tilemap& GetTilemap() const override {
		return Tilemap(math::ivec2::zero, math::ivec2::zero);
	}

	void UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft,
		const math::uivec2 bottomRight) override {}
	
	void Draw(sf::RenderTarget& target) const override {}
};

class TilemapManager : public TilemapManagerBase{
public:
	TilemapManager() :
		tilemap_({10, 10}, {32, 32}){ //TODO remove magic number
		
	}

	void Init() {
		tilemap_.Init();
	}
	
	const Tilemap& GetTilemap() const override {
		return tilemap_;
	}

	void UpdateChunk(const std::vector<Tile>& tiles, const math::uivec2 topLeft, const math::uivec2 bottomRight) {
		tilemap_.UpdateChunk(tiles, topLeft, bottomRight);
	}

	void Draw(sf::RenderTarget& target) const {
		tilemap_.Draw(target);
	}
private:
	Tilemap tilemap_;
};

using ServiceTilemapManager = ServiceLocator<TilemapManagerBase, TilemapManagerNull>;
}

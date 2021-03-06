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

class TilemapManager : public TilemapManagerBase, public IService{
public:
	TilemapManager() :
		tilemap_({100, 100}, {10, 10}){ //TODO remove magic number
		
	}

	void Init() override;

	const Tilemap& GetTilemap() const override;

	void UpdateChunk(const std::vector<Tile>& tiles, math::uivec2 topLeft,
	                 math::uivec2 bottomRight) override;

	void Draw(sf::RenderTarget& target) const override;
private:
	Tilemap tilemap_; //TODO 1.0 Must be a list
};
}

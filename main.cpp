
#include <vector.h>

#include <engine.h>

class CellularAutomataSystem {
public:
    void Init() {
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);

        const alloy::math::uivec2 topLeft = { 1, 1 };
        const alloy::math::uivec2 bottomRight{ 5, 5 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

        for (auto& tile : tiles) {
            tile.SetSprite(4);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);
    }
	
    void OnUpdate() {
        alloy::debug::Log("Update");
    }

private:
    std::vector<int> tiles_;

    alloy::math::ivec2 tilemapSize_;
};

class CellularAutomata {
public:
	CellularAutomata(const alloy::EngineInitSettings& engineInitSettings) :
        engine_(engineInitSettings){
	}

    void Init() {
        engine_.Init();

        cellularAutomataSystem_.Init();
		
        engine_.AddCallbackUpdate([this]() {cellularAutomataSystem_.OnUpdate(); });
	}

	void Run() {
        engine_.Run();
	}
private:
    alloy::Engine engine_;
    CellularAutomataSystem cellularAutomataSystem_;
};

int main() {

    alloy::EngineInitSettings engineInitSettings{
        "CellularA Automata",
        alloy::math::ivec2(600, 600)
    };
	
    CellularAutomata cellularAutomata(engineInitSettings);

    cellularAutomata.Init();

    cellularAutomata.Run();

    return EXIT_SUCCESS;
}

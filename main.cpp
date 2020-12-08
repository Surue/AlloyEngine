#include <array>
#include <random>


#include <vector.h>

#include <engine.h>


class CellularAutomataSystem {
public:
    void Init() {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_int_distribution<> distrib(0, 1);
    	
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);

        const alloy::math::uivec2 topLeft = { 0, 0 };
        const alloy::math::uivec2 bottomRight{ 100, 100 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

    	//Generate random
        for (int& tile : tiles_) {
	        tile = distrib(gen);
        }

    	//Cellular automata
    	for(int i = 0; i < 4; i++) {
            CellularStep();
    	}

    	//Fill tiles sprites
        for (auto i = 0; i < tiles.size(); i++) {
            tiles[i].SetSprite(tiles_[i]);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);
    }
	
    void OnUpdate() {
        //alloy::debug::Log("Update");
    }

private:
    alloy::math::ivec2 IndexToCoords(const int index) const {
        return { index / tilemapSize_.x, index % tilemapSize_.x };
    }

    int CoordsToIndex(const alloy::math::ivec2 coords) const {
        return coords.x * tilemapSize_.x + coords.y;
    }

	void CellularStep() {
        alloy::debug::Log("Step");
        std::vector<int> nextStep;
        nextStep.reserve(tiles_.size());
        nextStep.insert(nextStep.begin(), tiles_.begin(), tiles_.end());

    	for(auto index = 0; index < tiles_.size(); index++) {
            const auto coords = IndexToCoords(index);

            int nbAliveNeighbors = 0;

            for (const auto neighborOffset : neighborOffset_) {
                const auto neighborCoords = coords + neighborOffset;

            	//Check for each coords to be inside current tilemap
            	if(neighborCoords.x < 0 || neighborCoords.y < 0 || neighborCoords.x >= tilemapSize_.x || neighborCoords.y >= tilemapSize_.y) {
                    continue;
            	}

            	if(tiles_[CoordsToIndex(neighborCoords)] == 1) {
                    nbAliveNeighbors++;
            	}
            }

            const auto currentStatus = tiles_[index];

            if (currentStatus == 1 && (nbAliveNeighbors == 1 || nbAliveNeighbors >= 4)) {
                nextStep[index] = 1;
            }
            else if (currentStatus == 0 && nbAliveNeighbors >= 5) {
                nextStep[index] = 1;
            }
            else {
                nextStep[index] = 0;
            }
    	}

        tiles_.clear();
        tiles_.insert(tiles_.begin(), nextStep.begin(), nextStep.end());
    }
	
    std::vector<int> tiles_;

    alloy::math::ivec2 tilemapSize_ {100, 100};

    std::array<alloy::math::ivec2, 8> neighborOffset_{ {
        {-1, -1},
        {0, -1},
        { 1, -1 },
        { -1, 0 },
        { 1, 0 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 }
    } };
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

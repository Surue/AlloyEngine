#include <array>
#include <random>


#include <vector.h>

#include <engine.h>


class CellularAutomataSystem {
public:
    void Init() {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_int_distribution<> distrib01(0, 1);
    	
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);

        const alloy::math::uivec2 topLeft = { 0, 0 };
        const alloy::math::uivec2 bottomRight{ 100, 100 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

    	//Generate random solide tiles
        for (int& tile : tiles_) {
        	if(distrib01(gen) == 0) {
                tile = freeTile_;
        	} else {
                tile = solidTile_;
        	}
        }

    	//Cellular automata
    	for(int i = 0; i < 4; i++) {
            CellularStep();
    	}

        const std::uniform_int_distribution<> distrib0100(0, 100);

    	////Generate random water
        for (int& tile : tiles_) {
            if (tile == freeTile_ && distrib0100(gen) > 66) {
                tile = waterTile_;
            }
        }
    	
    	//Fill tiles sprites
        for (auto i = 0; i < tiles.size(); i++) {
            tiles[i].SetSprite(tiles_[i]);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);
    }
	
    void OnUpdate() {
        timeBetweenUpdate++;

    	if(timeBetweenUpdate < timeBetweenUpdateInMS_) {
            return;
    	}
    	
        const alloy::math::uivec2 topLeft = { 0, 0 };
        const alloy::math::uivec2 bottomRight{ 100, 100 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
    	
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

        UpdateWater();

        //Fill tiles sprites
        for (auto i = 0; i < tiles.size(); i++) {
            tiles[i].SetSprite(tiles_[i]);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);

        timeBetweenUpdate = 0;
    }

private:
    alloy::math::ivec2 IndexToCoords(const int index) const {
        return { index / tilemapSize_.x, index % tilemapSize_.x };
    }

    int CoordsToIndex(const alloy::math::ivec2 coords) const {
        return coords.x * tilemapSize_.x + coords.y;
    }

	void UpdateWater() {
        std::vector<int> nextStep;
        nextStep.reserve(tiles_.size());
        nextStep.insert(nextStep.begin(), tiles_.begin(), tiles_.end());
    	
        for (auto index = 0; index < tiles_.size(); index++) {
            if(tiles_[index] == waterTile_) {
                const auto coord = IndexToCoords(index);
            	
	            //Check can fall down
                const auto downCoords = coord + alloy::math::ivec2{ 0, 1 };
                if (downCoords.y >= 0 && downCoords.y < tilemapSize_.y) {
                    const int downIndex = CoordsToIndex(downCoords);
                    if (tiles_[downIndex] == freeTile_) {
                        nextStep[index] = freeTile_;
                        nextStep[downIndex] = waterTile_;
                        continue;
                    }

                    //Check can go left down
                    const auto downLeftCoords = coord + alloy::math::ivec2{ -1, 1 };
                    if (downLeftCoords.x >= 0 && downLeftCoords.x < tilemapSize_.x) {
                        const int leftIndex = CoordsToIndex(downLeftCoords);
                        if (tiles_[leftIndex] == freeTile_) {
                            nextStep[index] = freeTile_;
                            nextStep[leftIndex] = waterTile_;
                            continue;
                        }
                    }

                    //Check can go right
                    const auto downRightCoords = coord + alloy::math::ivec2{ 1, 1 };
                    if (downRightCoords.x >= 0 && downRightCoords.x < tilemapSize_.x) {
	                    const int rightIndex = CoordsToIndex(downRightCoords);
                        if (tiles_[rightIndex] == freeTile_) {
                            nextStep[index] = freeTile_;
                            nextStep[rightIndex] = waterTile_;
                            continue;
                        }
                    }
                }

            }
        }

        tiles_.clear();
        tiles_.insert(tiles_.begin(), nextStep.begin(), nextStep.end());
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

            	if(tiles_[CoordsToIndex(neighborCoords)] == freeTile_) {
                    nbAliveNeighbors++;
            	}
            }

            const auto currentStatus = tiles_[index];

            if (currentStatus == freeTile_ && (nbAliveNeighbors == 1 || nbAliveNeighbors >= 4)) {
                nextStep[index] = freeTile_;
            }
            else if (currentStatus == solidTile_ && nbAliveNeighbors >= 5) {
                nextStep[index] = freeTile_;
            }
            else {
                nextStep[index] = solidTile_;
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

    const int solidTile_ = 10;
    const int freeTile_ = 13;
    const int waterTile_ = 6;
    const int timeBetweenUpdateInMS_ = 10;
    int timeBetweenUpdate = 0;
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

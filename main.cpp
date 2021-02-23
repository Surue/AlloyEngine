#include <array>
#include <random>

#include <lib/Remotery.h>

#include <application.h>

class CellularAutomataSystem {
public:
    void Init() {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_int_distribution<> distrib01(0, 1);
    	
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);
        tileStates_.resize(tiles_.size());
        waterPressure_.resize(tiles_.size());

        const math::uivec2 topLeft = { 0, 0 };
        const math::uivec2 bottomRight{ 100, 100 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

    	//Generate random solide tiles
    	for(int i = 0; i < nbTiles; i++) {
            if (distrib01(gen) == 0) {
                tiles_[i] = freeTile_;
            }
            else {
                tiles_[i] = solidTile_;
            }
    	}

    	//Cellular automata
    	for(int i = 0; i < 4; i++) {
            CellularStep();
    	}

        for (int i = 0; i < nbTiles; i++) {
            if (tiles_[i] == freeTile_) {
                tileStates_[i] = TileState::AIR;
            }
            else {
                tileStates_[i] = TileState::SOLID;
            }
        }

        const std::uniform_int_distribution<> distrib0100(0, 100);

    	////Generate random water
        for (int index = 0; index < tiles_.size(); index++) {
            if (tileStates_[index] == TileState::AIR && distrib0100(gen) > 66) {
                waterPressure_[index] = maxPressure_;
                tileStates_[index] = TileState::LIQUID;
            }else if(tiles_[index] == freeTile_){
                waterPressure_[index] = 0;
            }else {
                waterPressure_[index] = invalidWaterPressure_; 
            }
        }
    	
    	//Fill tiles sprites
        for (auto i = 0; i < tiles.size(); i++) {
            tiles[i].SetSprite(tiles_[i]);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);
    }
	
    void OnUpdate() {
    	//Update Water
        timeBetweenUpdate_++;

    	if(timeBetweenUpdate_ < timeBetweenUpdateInMS_) {
            return;
    	}
    	
        const math::uivec2 topLeft = { 0, 0 };
        const math::uivec2 bottomRight{ 100, 100 };

        const int nbTiles = (bottomRight.x - topLeft.x) * (bottomRight.y - topLeft.y);
    	
        alloy::graphics::Tile baseTile = alloy::graphics::Tile(alloy::graphics::ServiceTilemapManager::Get().GetTilemap().GetTileset(), 0);
        std::vector<alloy::graphics::Tile> tiles(nbTiles, baseTile);

    	//Update water
        UpdateWater();

        //Fill tiles sprites
        for (auto i = 0; i < tiles.size(); i++) {
            tiles[i].SetSprite(tiles_[i]);
        }

        alloy::graphics::ServiceTilemapManager::Get().UpdateChunk(tiles, topLeft, bottomRight);

        timeBetweenUpdate_ = 0;
    }

private:
    math::ivec2 IndexToCoords(const int index) const {
        return { index / tilemapSize_.x, index % tilemapSize_.x };
    }

    int CoordsToIndex(const math::ivec2 coords) const {
        return coords.x * tilemapSize_.x + coords.y;
    }

    float CalculateVerticalFlowValue(const float remainingLiquid, const int indexDest)
    {
        const float sum = remainingLiquid + waterPressure_[indexDest];

        if (sum <= maxPressure_) {
            return maxPressure_;
        }
        else if (sum < 2.0f * maxPressure_ + maxCompression_) {
            return (maxPressure_ * maxPressure_ + sum * maxCompression_) / (maxPressure_ + maxCompression_);
        }
        else {
            return (sum + maxCompression_) / 2.0f;
        }
    }

    void UpdateWater() {
        std::vector<float> diffs(waterPressure_.size());
        std::fill(diffs.begin(), diffs.end(), 0);

        for (size_t index = 0; index < waterPressure_.size(); index++) {
            // Only work with tiles that can hold water
            if (tileStates_[index] == TileState::SOLID) continue;
        	
            const auto coords = IndexToCoords(index);

            //1. Give to down
            float remainingPressure = waterPressure_[index];
            if (remainingPressure <= 0) continue;
        	
            const auto downCoords = coords + math::ivec2::down;
                
            //Check valid coords
            if (downCoords.y < tilemapSize_.y) {
	            const int downIndex = CoordsToIndex(downCoords);
                const float downPressure = waterPressure_[downIndex];

	            //Water pressure under bust be less than max and not equal to invalidWaterPressure
	            if (tileStates_[downIndex] != TileState::SOLID) {
		            float flow = CalculateVerticalFlowValue(waterPressure_[index], downIndex) - downPressure;

                    if (downPressure > 0 && flow > minFlow_)
                        flow *= flowSpeed_;

                    // Constrain flow
                    flow = std::max(flow, 0.0f);
                    if (flow > std::min(maxFlow_, waterPressure_[index]))
                        flow = std::min(maxFlow_, waterPressure_[index]);

                    if (flow != 0.0f) {
                        diffs[downIndex] += flow;
                        diffs[index] -= flow;
                        remainingPressure -= flow;
                    }
	            }
            }
            
            if (remainingPressure < minPressure_) {
                continue;
            }
        	
            //2. Equalize left  
        	
            const auto leftCoords = coords + math::ivec2::left;

            // Check valid coords
            if (leftCoords.x >= 0) {
	            const int leftIndex = CoordsToIndex(leftCoords);
	            const float leftPressure = waterPressure_[leftIndex];

	            //Water pressure under bust be less than max and not equal to invalidWaterPressure
	            if (tileStates_[leftIndex] != TileState::SOLID) {
		            float flow = (remainingPressure - leftPressure) / 4.0f;
                    if(flow > minFlow_)
                        flow *= flowSpeed_;
	            	
                    flow = std::max(flow, 0.0f);
	            	
	            	if(flow > std::min(maxFlow_, remainingPressure)) {
                        flow = std::min(maxFlow_, remainingPressure);
	            	}

                    if (flow != 0.0f) {
                        diffs[leftIndex] += flow;
                        diffs[index] -= flow;
                        remainingPressure -= flow;
                    }
	            }
            }

            if (remainingPressure < minPressure_) {
                continue;
            }

            //2. Equalize right  

            const auto rightCoords = coords + math::ivec2::right;

            // Check valid coords
            if (rightCoords.x < tilemapSize_.x) {
                const int rightIndex = CoordsToIndex(rightCoords);
                const float rightPressure = waterPressure_[rightIndex];

                //Water pressure under bust be less than max and not equal to invalidWaterPressure
                if (tileStates_[rightIndex] != TileState::SOLID) {
                    float flow = (remainingPressure - rightPressure) / 3.0f;
                    if (flow > minFlow_)
                        flow *= flowSpeed_;

                    flow = std::max(flow, 0.0f);

                    if (flow > std::min(maxFlow_, remainingPressure)) {
                        flow = std::min(maxFlow_, remainingPressure);
                    }

                    if (flow != 0.0f) {
                        diffs[rightIndex] += flow;
                        diffs[index] -= flow;
                        remainingPressure -= flow;
                    }
                }
            }

            if (remainingPressure < minPressure_) {
                continue;
            }

        	// 4. Flow upwards

            const auto upCoords = coords + math::ivec2::up;
            if (upCoords.y >= 0) {
                const int upIndex = CoordsToIndex(upCoords);

                if (tileStates_[upIndex] != TileState::SOLID) {

                    float flow = remainingPressure - CalculateVerticalFlowValue(remainingPressure, upIndex);
                    if (flow > minFlow_)
                        flow *= flowSpeed_;

                    // constrain flow
                    flow = std::max(flow, 0.0f);
                    if (flow > std::min(maxFlow_, remainingPressure))
                        flow = std::min(maxFlow_, remainingPressure);
                	
                    // Adjust values
                    if (flow != 0.0f) {
                        remainingPressure -= flow;
                        diffs[index] -= flow;
                        diffs[upIndex] += flow;
                    }
                }
            }
        }

    	//Update diff
    	for(int i = 0; i < diffs.size(); i++) {
            waterPressure_[i] += diffs[i];
    	}

        float totalPressure = 0;
        for (auto index = 0; index < waterPressure_.size(); index++) {
            if (tileStates_[index] == TileState::SOLID) continue;
        	
            totalPressure += waterPressure_[index];
        	
            if (waterPressure_[index] <= 0) { //Air
                tiles_[index] = freeTile_;
                tileStates_[index] = TileState::AIR;
            }else  if (waterPressure_[index] <= maxPressure_ * 0.5f) {
                tiles_[index] = waterTile1_;
                tileStates_[index] = TileState::LIQUID;
            }
            else if (waterPressure_[index] <= maxPressure_) {
                tiles_[index] = waterTile2_;
                tileStates_[index] = TileState::LIQUID;
            }
            else if (waterPressure_[index] <= maxPressure_ + maxCompression_) {
                tiles_[index] = waterTile3_;
                tileStates_[index] = TileState::LIQUID;
            }
            else if (waterPressure_[index] <= maxPressure_ + 2 * maxCompression_) {
                tiles_[index] = waterTile4_;
                tileStates_[index] = TileState::LIQUID;
            }
            else if (waterPressure_[index] > maxPressure_ + 2 * maxCompression_) {
                tiles_[index] = waterTile5_;
                tileStates_[index] = TileState::LIQUID;
            }
        }
    }

	void CellularStep() {
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

    std::vector<float> waterPressure_;

    math::ivec2 tilemapSize_ {100, 100};

	enum class TileState : uint8_t {
		SOLID = 0,
		LIQUID,
		AIR
	};

    std::vector<TileState> tileStates_;

    std::array<math::ivec2, 8> neighborOffset_{ {
        {-1, -1},
        {0, -1},
        { 1, -1 },
        { -1, 0 },
        { 1, 0 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 }
    } };

	//Tiles indexs
    const int solidTile_ = 10;
    const int freeTile_ = 13;
	
    const int waterTile1_ = 0;
    const int waterTile2_ = 1;
    const int waterTile3_ = 2;
    const int waterTile4_ = 3;
    const int waterTile5_ = 4;
	
    const int timeBetweenUpdateInMS_ = 50;
    const float maxPressure_ = 1.0f;
    const float maxCompression_ = 0.25f;
    const float minFlow_ = 1.0f;
    const float maxFlow_ = 4.0f;
    const float flowSpeed_ = 1.0f;
    const float minPressure_ = 0.005f;
    const int invalidWaterPressure_ = -1;
    int timeBetweenUpdate_ = 0;
};

class CellularAutomata : public alloy::Application{
public:
	CellularAutomata(const alloy::ApplicationInitSettings& applicationInitSettings) : Application(applicationInitSettings){
	}

protected:
    void Init() override {
        cellularAutomataSystem_.Init();

        AddCallbackUpdate([this]() {cellularAutomataSystem_.OnUpdate(); });
    }

private:
    CellularAutomataSystem cellularAutomataSystem_;
};

int main() {
    Remotery* rmt;
    rmt_CreateGlobalInstance(&rmt);
    alloy::ApplicationInitSettings engineInitSettings{
        "CellularA Automata",
        math::ivec2(600, 600)
    };
	
    CellularAutomata cellularAutomata(engineInitSettings);

    cellularAutomata.Start();

    rmt_DestroyGlobalInstance(rmt);
    return EXIT_SUCCESS;
}

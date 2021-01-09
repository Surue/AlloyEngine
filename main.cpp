#include <array>
#include <random>


#include <vector.h>

#include <engine.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


class CellularAutomataSystem {
public:
    void Init() {
        std::random_device rd;
        std::mt19937 gen(rd());
        const std::uniform_int_distribution<> distrib01(0, 1);
    	
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);
        waterPressure_.resize(tiles_.size());

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
        for (int index = 0; index < tiles_.size(); index++) {
            if (tiles_[index] == freeTile_ && distrib0100(gen) > 66) {
                waterPressure_[index] = defaultPressure_;
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
        timeBetweenUpdate_++;

    	if(timeBetweenUpdate_ < timeBetweenUpdateInMS_) {
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

        timeBetweenUpdate_ = 0;
    }

private:
    alloy::math::ivec2 IndexToCoords(const int index) const {
        return { index / tilemapSize_.x, index % tilemapSize_.x };
    }

    int CoordsToIndex(const alloy::math::ivec2 coords) const {
        return coords.x * tilemapSize_.x + coords.y;
    }

    /// <summary>
    /// Update take place on a second tileset, then they are swa, tiles updates only themselves 
    /// 1. First loop, up/down
    /// 2. Second loop, down-left
    /// 3. Third loop, down-right
    /// 3. Fourth loop, left/right
    /// </summary>
    void UpdateWater() {
        std::vector<int> nextStepPressure;
        nextStepPressure.reserve(waterPressure_.size());
        nextStepPressure.insert(nextStepPressure.begin(), waterPressure_.begin(), waterPressure_.end());

    	// First loop water move up/down
        for (auto index = 0; index < waterPressure_.size(); index++) {
            //TODO optimisation needed, because every tiles is updated
            if (waterPressure_[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

                //1. Check can fall down
                if (waterPressure_[index] > 0) {
                    const auto downCoords = coords + alloy::math::ivec2{ 0, 1 };
                    if (downCoords.y < tilemapSize_.y) {
                        const int downIndex = CoordsToIndex(downCoords);

                        //Water pressure under bust be less than max and not equal to invalidWaterPressure
                        if (waterPressure_[downIndex] != invalidWaterPressure_ && waterPressure_[downIndex] < defaultPressure_) {
                            nextStepPressure[index] -= std::min(waterPressure_[index], defaultPressure_ - waterPressure_[downIndex]);
                        }
                    }
                }

                if (nextStepPressure[index] < 0) {
                    alloy::debug::LogError("negativePressure");
                }

                //3. Get water from top
                //If tile is full, no need to go further
                if (waterPressure_[index] == defaultPressure_) {
                    continue;
                }

                const auto upCoords = coords + alloy::math::ivec2{ 0, -1 };
                if (upCoords.y >= 0) {
                    const int upIndex = CoordsToIndex(upCoords);
                    if (waterPressure_[upIndex] > 0) {
                        nextStepPressure[index] += std::min(waterPressure_[upIndex], defaultPressure_ - waterPressure_[index]);
                    }
                }

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("max pressure >");
                }
            }
        }

        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());

    	// Second loop water move down-left/down-right
        for (auto index = 0; index < nextStepPressure.size(); index++) {
            if (nextStepPressure[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

                //Check down-left
                const auto downLeftCoords = coords + alloy::math::ivec2{ -1, 1 };
                if (downLeftCoords.x >= 0 && downLeftCoords.x < tilemapSize_.x && downLeftCoords.y < tilemapSize_.y) {
                    const auto leftCoords = coords + alloy::math::ivec2{ -1, 0 };
                    const auto downCoords = coords + alloy::math::ivec2{ 0, 1 };
                    const int downLeftIndex = CoordsToIndex(downLeftCoords);
                    const int leftIndex = CoordsToIndex(leftCoords);
                    const int downIndex = CoordsToIndex(downCoords);
                	if((waterPressure_[leftIndex] != invalidWaterPressure_ || waterPressure_[downIndex] != invalidWaterPressure_) && waterPressure_[downLeftIndex] != invalidWaterPressure_ && waterPressure_[downLeftIndex] < defaultPressure_){
                        nextStepPressure[index] -= std::min(waterPressure_[index], defaultPressure_ - waterPressure_[downLeftIndex]);
                    }
                }

            	//Check can take water
                if (waterPressure_[index] == defaultPressure_) {
                    continue;
                }

                //Check up-right
                const auto upRightCoords = coords + alloy::math::ivec2{ 1, -1 };
                if (upRightCoords.x >= 0 && upRightCoords.x < tilemapSize_.x && upRightCoords.y >= 0) {
                    const auto rightCoords = coords + alloy::math::ivec2{ 1, 0 };
                    const auto upCoords = coords + alloy::math::ivec2{ 0, -1 };
                    const int upRightIndex = CoordsToIndex(upRightCoords);
                    const int rightIndex = CoordsToIndex(rightCoords);
                    const int upIndex = CoordsToIndex(upCoords);
                    if ((waterPressure_[rightIndex] != invalidWaterPressure_ || waterPressure_[upIndex] != invalidWaterPressure_) && waterPressure_[upRightIndex] != invalidWaterPressure_ && waterPressure_[upRightIndex] > 0) {
                        nextStepPressure[index] += std::min(waterPressure_[upRightIndex], defaultPressure_ - waterPressure_[index]);
                    }
                }

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("> default pressure");
                }
            }
        }
    	
        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());

        // Third loop water move down-right
        for (auto index = 0; index < nextStepPressure.size(); index++) {
            if (nextStepPressure[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

                //Check down-right
                const auto downRightCoords = coords + alloy::math::ivec2{ 1, 1 };
                if (downRightCoords.x >= 0 && downRightCoords.x < tilemapSize_.x && downRightCoords.y < tilemapSize_.y) {
                    const auto rightCoords = coords + alloy::math::ivec2{ 1, 0 };
                    const auto downCoords = coords + alloy::math::ivec2{ 0, 1 };
                    const int downRightIndex = CoordsToIndex(downRightCoords);
                    const int rightIndex = CoordsToIndex(rightCoords);
                    const int downIndex = CoordsToIndex(downCoords);
                    if ((waterPressure_[rightIndex] != invalidWaterPressure_ || waterPressure_[downIndex] != invalidWaterPressure_) && waterPressure_[downRightIndex] != invalidWaterPressure_ && waterPressure_[downRightIndex] < defaultPressure_) {
                        nextStepPressure[index] -= std::min(waterPressure_[index], defaultPressure_ - waterPressure_[downRightIndex]);
                    }
                }

                //Check can take water
                if (waterPressure_[index] == defaultPressure_) {
                    continue;
                }

                //Check up-left
                const auto upLeftCoords = coords + alloy::math::ivec2{ -1, -1 };
                if (upLeftCoords.x >= 0 && upLeftCoords.x < tilemapSize_.x && upLeftCoords.y >= 0) {
                    const auto leftCoords = coords + alloy::math::ivec2{ -1, 0 };
                    const auto upCoords = coords + alloy::math::ivec2{ 0, -1 };
                    const int upLeftIndex = CoordsToIndex(upLeftCoords);
                    const int leftIndex = CoordsToIndex(leftCoords);
                    const int upIndex = CoordsToIndex(upCoords);
                    if ((waterPressure_[leftIndex] != invalidWaterPressure_ || waterPressure_[upIndex] != invalidWaterPressure_) && waterPressure_[upLeftIndex] != invalidWaterPressure_ && waterPressure_[upLeftIndex] > 0) {
                        nextStepPressure[index] += std::min(waterPressure_[upLeftIndex], defaultPressure_ - waterPressure_[index]);
                    }
                }

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("> default pressure");
                }
            }
        }

        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());
    	
    	// fourth loop water move left/right
        for (auto index = 0; index < nextStepPressure.size(); index++) {
            //TODO optimisation needed, because every tiles is updated
            if (nextStepPressure[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

                int diff = 0;

                //Check left
                const auto leftCoords = coords + alloy::math::ivec2{ -1, 0 };
                if (leftCoords.x >= 0 && leftCoords.x < tilemapSize_.x) {
                    const int leftIndex = CoordsToIndex(leftCoords);
                    if (waterPressure_[leftIndex] != invalidWaterPressure_) {
                        int equilibrium = std::floor((waterPressure_[leftIndex] + waterPressure_[index]) * 0.5f);
                        int leftDiff = std::min(std::abs(equilibrium - waterPressure_[index]), std::abs(waterPressure_[leftIndex] - equilibrium)) * sgn(equilibrium - waterPressure_[index]);
                        //alloy::debug::Log("left[" + std::to_string(waterPressure_[leftIndex]) + "], Index[" + std::to_string(waterPressure_[index]) + "] => equilibrium: " + std::to_string(equilibrium) + ", diff : " + std::to_string(leftDiff));

                        diff += leftDiff;
                    }
                }

            	//Check right
                const auto rightCoords = coords + alloy::math::ivec2{ 1, 0 };
                if (rightCoords.x >= 0 && rightCoords.x < tilemapSize_.x) {
                    const int rightIndex = CoordsToIndex(rightCoords);
                    if (waterPressure_[rightIndex] != invalidWaterPressure_) {
                        int equilibrium = std::floor((waterPressure_[rightIndex] + waterPressure_[index]) * 0.5f);
                        int rightDiff = std::min(std::abs(equilibrium - waterPressure_[index]), std::abs(waterPressure_[rightIndex] - equilibrium)) * sgn(equilibrium - waterPressure_[index]);
                        //alloy::debug::Log("right[" + std::to_string(waterPressure_[rightIndex]) + "], Index[" + std::to_string(waterPressure_[index]) + "] => equilibrium: " + std::to_string(equilibrium) + ", diff : " + std::to_string(rightDiff));
                        diff += rightDiff;
                    }
                }

                nextStepPressure[index] += diff;

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("> default pressure");
                }
            }
        }

        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());

        std::vector<int> previousTiles;
        previousTiles.reserve(tiles_.size());
        previousTiles.insert(previousTiles.begin(), tiles_.begin(), tiles_.end());

        int totalPressure = 0;
        for (auto index = 0; index < waterPressure_.size(); index++) {
            totalPressure += waterPressure_[index];
            if (waterPressure_[index] > defaultPressure_) {
                tiles_[index] = 0;
            }
            else if (waterPressure_[index] <= defaultPressure_ && waterPressure_[index] >= defaultPressure_ * 0.5f) {
                tiles_[index] = waterTile_;
            }
            else if (waterPressure_[index] < defaultPressure_ * 0.5f && waterPressure_[index] > 0) {
                tiles_[index] = waterTile_ - 1;
            }
            else if (waterPressure_[index] == invalidWaterPressure_) {
                tiles_[index] = previousTiles[index];
            }
            else {
                tiles_[index] = freeTile_;
            }
        }
        alloy::debug::Log(std::to_string(totalPressure));
    }

	/// <summary>
	/// Update take place on a second tileset, then they are swa, tiles updates only themselves 
	/// 1. Go Down
	/// 2. Flow Left / Right
	/// 3. Get from up
	/// </summary>
	void UpdateWater1() {
        std::vector<int> nextStepPressure;
        nextStepPressure.reserve(waterPressure_.size());
        nextStepPressure.insert(nextStepPressure.begin(), waterPressure_.begin(), waterPressure_.end());
    	
        for (auto index = 0; index < waterPressure_.size(); index++) {
        	//TODO optimisation needed, because every tiles is updated
            if(waterPressure_[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

	            //1. Check can fall down
                if (waterPressure_[index] > 0) {
                    const auto downCoords = coords + alloy::math::ivec2{ 0, 1 };
                    if (downCoords.y < tilemapSize_.y) {
                        const int downIndex = CoordsToIndex(downCoords);

                        //Water pressure under bust be less than max and not equal to invalidWaterPressure
                        if (waterPressure_[downIndex] != invalidWaterPressure_ && waterPressure_[downIndex] < defaultPressure_) {
                            nextStepPressure[index] -= std::min(waterPressure_[index], defaultPressure_ - waterPressure_[downIndex]);
                        }
                    }
                }

            	if(nextStepPressure[index] < 0) {
                    alloy::debug::LogError("negativePressure");
            	}

				//3. Get water from top
                //If tile is full, no need to go further
            	if(waterPressure_[index] == defaultPressure_) {
                    continue;
            	}

                const auto upCoords = coords + alloy::math::ivec2{ 0, -1 };
                if (upCoords.y >= 0) {
                    const int upIndex = CoordsToIndex(upCoords);
                    if (waterPressure_[upIndex] > 0) {
                        nextStepPressure[index] += std::min(waterPressure_[upIndex], defaultPressure_ - waterPressure_[index]);
                    }
                }

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("max pressure >");
                }
            }
        }

        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());

        for (auto index = 0; index < nextStepPressure.size(); index++) {
            //TODO optimisation needed, because every tiles is updated
            if (nextStepPressure[index] != invalidWaterPressure_) {
                const auto coords = IndexToCoords(index);

                int diff = 0;
            	
            	//Check left
                const auto leftCoords = coords + alloy::math::ivec2{-1, 0};
            	if(leftCoords.x >= 0 && leftCoords.x < tilemapSize_.x) {
                    const int leftIndex = CoordsToIndex(leftCoords);
                    if (waterPressure_[leftIndex] != invalidWaterPressure_) {
                        int equilibrium = std::floor((waterPressure_[leftIndex] + waterPressure_[index]) * 0.5f);
                    	int leftDiff = std::min(std::abs(equilibrium - waterPressure_[index]), std::abs(waterPressure_[leftIndex] - equilibrium)) * sgn(equilibrium - waterPressure_[index]);
                        //alloy::debug::Log("left[" + std::to_string(waterPressure_[leftIndex]) + "], Index[" + std::to_string(waterPressure_[index]) + "] => equilibrium: " + std::to_string(equilibrium) + ", diff : " + std::to_string(leftDiff));

                    	diff += leftDiff;
                    }
            	}

                const auto rightCoords = coords + alloy::math::ivec2{ 1, 0 };
                if (rightCoords.x >= 0 && rightCoords.x < tilemapSize_.x) {
                    const int rightIndex = CoordsToIndex(rightCoords);
                    if (waterPressure_[rightIndex] != invalidWaterPressure_) {
                        int equilibrium = std::floor((waterPressure_[rightIndex] + waterPressure_[index]) * 0.5f);
                        int rightDiff = std::min(std::abs(equilibrium - waterPressure_[index]), std::abs(waterPressure_[rightIndex] - equilibrium)) * sgn(equilibrium - waterPressure_[index]);
                        //alloy::debug::Log("right[" + std::to_string(waterPressure_[rightIndex]) + "], Index[" + std::to_string(waterPressure_[index]) + "] => equilibrium: " + std::to_string(equilibrium) + ", diff : " + std::to_string(rightDiff));
                        diff += rightDiff;
                    }
                }

                nextStepPressure[index] += diff;

                if (nextStepPressure[index] > defaultPressure_) {
                    alloy::debug::LogError("> default pressure");
                }
            }
        }
        
        waterPressure_.clear();
        waterPressure_.insert(waterPressure_.begin(), nextStepPressure.begin(), nextStepPressure.end());

        std::vector<int> previousTiles;
        previousTiles.reserve(tiles_.size());
        previousTiles.insert(previousTiles.begin(), tiles_.begin(), tiles_.end());

        int totalPressure = 0;
    	for(auto index = 0; index < waterPressure_.size(); index++) {
            totalPressure += waterPressure_[index];
    		if(waterPressure_[index] > defaultPressure_) {
                tiles_[index] = 0;
    		} else if (waterPressure_[index] <= defaultPressure_ && waterPressure_[index] >= defaultPressure_ * 0.5f) {
                tiles_[index] = waterTile_;
    		} else if(waterPressure_[index] < defaultPressure_ * 0.5f && waterPressure_[index] > 0) {
                tiles_[index] = waterTile_ - 1;
    		} else if(waterPressure_[index] == invalidWaterPressure_){
                tiles_[index] = previousTiles[index];
    		}else {
                tiles_[index] = freeTile_;
    		}
    	}
        alloy::debug::Log(std::to_string(totalPressure));
    }

	//Update take place on the same tiles
	//1. Go Down
	//2. Go Down Left / Down Right
	//3. Go Left / Right
	void UpdateWater2() {
    	//TODO Each cell must handle taking and giving water!!!
        //std::vector<int> nextStep;
        //nextStep.reserve(waterPressure_.size());
        //nextStep.insert(nextStep.begin(), waterPressure_.begin(), waterPressure_.end());
    	
    	//Move water following pressure
        for (auto index = 0; index < waterPressure_.size(); index++) {
            if(waterPressure_[index] > 0) {
                const auto coords = IndexToCoords(index);
            	
	            //Check can fall down
                const auto downCoords = coords + alloy::math::ivec2{ 0, 1 };
                if (downCoords.y >= 0 && downCoords.y < tilemapSize_.y) {
                    const int downIndex = CoordsToIndex(downCoords);
                    if (waterPressure_[downIndex] >= 0 && waterPressure_[downIndex] < waterPressure_[index]) {
                        if (waterPressure_[downIndex] <= defaultPressure_) { //Transfert all the water
                            const auto diff = std::min(waterPressure_[index], defaultPressure_ - waterPressure_[downIndex]);
                            waterPressure_[index] = waterPressure_[index] - diff;
                            waterPressure_[downIndex] = waterPressure_[downIndex] + diff;
                            continue;
                        } 
                    }
                    
                    //Check can go left down
                    const auto downLeftCoords = coords + alloy::math::ivec2{ -1, 1 };
                   
                    if (downLeftCoords.x >= 0 ) {
                        const auto leftIndex = CoordsToIndex(downLeftCoords);
                        if (waterPressure_[leftIndex] >= 0 && waterPressure_[leftIndex] < waterPressure_[index]) {
                            if (waterPressure_[leftIndex] <= defaultPressure_) {
                                const auto diff = std::min(waterPressure_[index], defaultPressure_ - waterPressure_[leftIndex]);
                                waterPressure_[index] = waterPressure_[index] - diff;
                                waterPressure_[leftIndex] = waterPressure_[leftIndex] + diff;
                                continue;
                            }
                        }
                    }

                    ////Check can go right
                    const auto downRightCoords = coords + alloy::math::ivec2{ 1, 1 };
                    if (downRightCoords.x < tilemapSize_.x) {
	                    const auto rightIndex = CoordsToIndex(downRightCoords);
                        if (waterPressure_[rightIndex] >= 0 && waterPressure_[rightIndex] < waterPressure_[index]) {
                            if (waterPressure_[rightIndex] <= defaultPressure_) {
                                const auto diff = std::min(waterPressure_[index], defaultPressure_ - waterPressure_[rightIndex]);
                                waterPressure_[index] = waterPressure_[index] - diff;
                                waterPressure_[rightIndex] = waterPressure_[rightIndex] + diff;
                                continue;
                            }
                        }
                    }

                }

                //Check can go left 
                const auto leftCoords = coords + alloy::math::ivec2{ -1, 0 };
                bool transfertLeft = false;
                int leftIndex = 0;
                if (leftCoords.x >= 0 && leftCoords.x < tilemapSize_.x) {
                    leftIndex = CoordsToIndex(leftCoords);
                    if (waterPressure_[leftIndex] >= 0 && waterPressure_[leftIndex] < waterPressure_[index]) {
                        if (waterPressure_[leftIndex] <= defaultPressure_) {
                            transfertLeft = true;
                        }
                    }
                }

                //Check can go right 
                const auto rightCoords = coords + alloy::math::ivec2{ 1, 0 };
                bool transfertRight = false;
                int rightIndex = 0;
                if (rightCoords.x >= 0 && rightCoords.x < tilemapSize_.x) {
                    rightIndex = CoordsToIndex(rightCoords);
                    if (waterPressure_[rightIndex] >= 0 && waterPressure_[rightIndex] < waterPressure_[index]) {
                        if (waterPressure_[rightIndex] <= defaultPressure_) {
                            transfertRight = true;
                        }
                    }
                }

                if (transfertLeft && transfertRight) {
                    const int total = waterPressure_[leftIndex] + waterPressure_[index] + waterPressure_[rightIndex];
                    const int third = std::floor(total / 3.0f);
                    const int remaining = total - third * 3;

                    waterPressure_[index] = third + remaining;
                    waterPressure_[leftIndex] = third;
                    waterPressure_[rightIndex] = third;
                }
                else if (transfertLeft) {
                    const int total = waterPressure_[leftIndex] + waterPressure_[index];
                    const int half = std::floor(total * 0.5f);
                    const int remaining = total - half * 2;

                    waterPressure_[index] = half + remaining;
                    waterPressure_[leftIndex] = half;
                }
                else if (transfertRight) {
                    const int total = waterPressure_[rightIndex] + waterPressure_[index];
                    const int half = std::floor(total * 0.5f);
                    const int remaining = total - half * 2;

                    waterPressure_[index] = half + remaining;
                    waterPressure_[rightIndex] = half;
                }
            }
        }
        
    std::vector<int> previousTiles;
    previousTiles.reserve(tiles_.size());
    previousTiles.insert(previousTiles.begin(), tiles_.begin(), tiles_.end());

    for (auto index = 0; index < waterPressure_.size(); index++) {
        if (waterPressure_[index] > defaultPressure_) {
            tiles_[index] = 0;
        }
        else if (waterPressure_[index] <= defaultPressure_ && waterPressure_[index] >= defaultPressure_ * 0.5f) {
            tiles_[index] = waterTile_;
        }
        else if (waterPressure_[index] < defaultPressure_ * 0.5f && waterPressure_[index] > 0) {
            tiles_[index] = waterTile_ - 1;
        }
        else if (waterPressure_[index] == -1) {
            tiles_[index] = previousTiles[index];
        }
        else {
            tiles_[index] = freeTile_;
        }
    }
    //tiles_.insert(tiles_.begin(), nextStep.begin(), nextStep.end());
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

    std::vector<int> waterPressure_;

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
    const int timeBetweenUpdateInMS_ = 50;
    const int defaultPressure_ = 10;
    const int invalidWaterPressure_ = -1;
    int timeBetweenUpdate_ = 0;
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

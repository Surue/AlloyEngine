#include <water_simulation_system.h>

#include <tile.h>

#include "entity_manager.h"

void WaterSimulationSystem::OnInit() {

	std::random_device rd;
	std::mt19937 gen(rd());
	const std::uniform_int_distribution<> distrib01(0, 1);

	tiles_.resize(tilemapSize_.x * tilemapSize_.y);
	tileStates_.resize(tiles_.size());
	waterPressure_.resize(tiles_.size());

	const uint32_t nbTiles = (bottomRight_.x - topLeft_.x) * (bottomRight_.y - topLeft_.y);
	const alloy::graphics::Tile baseTile = alloy::graphics::Tile(tilemapManager_.GetTilemap().GetTileset(), 0);
	tilesToUpdate = std::vector<alloy::graphics::Tile>(nbTiles, baseTile);

	//Generate random solide tiles
	for (auto i = 0; i < nbTiles; i++) {
		if (distrib01(gen) == 0) {
			tiles_[i] = freeTile_;
		} else {
			tiles_[i] = solidTile_;
		}
	}

	//Cellular automata
	for (auto i = 0; i < 4; i++) {
		CellularStep();
	}

	for (auto i = 0; i < nbTiles; i++) {
		if (tiles_[i] == freeTile_) {
			tileStates_[i] = TileState::AIR;
		} else {
			tileStates_[i] = TileState::SOLID;
		}
	}

	const std::uniform_int_distribution<> distrib0100(0, 100);

	//Generate random water
	for (int index = 0; index < tiles_.size(); index++) {
		if (tileStates_[index] == TileState::AIR && distrib0100(gen) > 66) {
			waterPressure_[index] = maxPressure_;
			tileStates_[index] = TileState::LIQUID;
		} else if (tiles_[index] == freeTile_) {
			waterPressure_[index] = 0.0f;
		} else {
			waterPressure_[index] = static_cast<float>(invalidWaterPressure_);
		}
	}

	//Fill tiles sprites
	for (size_t i = 0; i < tilesToUpdate.size(); i++) {
		tilesToUpdate[i].SetSprite(tiles_[i]);
	}

	tilemapManager_.UpdateChunk(tilesToUpdate, topLeft_, bottomRight_);

	//Create two lights
	auto& entityManager = alloy::ServiceLocator::Get<alloy::ecs::EntityManager>();
	const auto entity1 = entityManager.CreateEntity();

	const auto entity1Position = alloy::ecs::Position{ math::fvec2{300, 300} };
	entityManager.AddComponentData(entity1, static_cast<alloy::ecs::Component>(alloy::ecs::CoreComponent::POSITION), reinterpret_cast<const alloy::ecs::IComponentData&>(entity1Position));
	const auto entity1Light = alloy::ecs::Light{ alloy::Color::fuchsia, alloy::ecs::LightType::POINT_LIGHT, 300};
	entityManager.AddComponentData(entity1, static_cast<alloy::ecs::Component>(alloy::ecs::CoreComponent::LIGHT), reinterpret_cast<const alloy::ecs::IComponentData&>(entity1Light));

	const auto entity2 = entityManager.CreateEntity();

	const auto entity2Position = alloy::ecs::Position{ math::fvec2{300, 150} };
	entityManager.AddComponentData(entity2, static_cast<alloy::ecs::Component>(alloy::ecs::CoreComponent::POSITION), reinterpret_cast<const alloy::ecs::IComponentData&>(entity2Position));
	const auto entity2Light = alloy::ecs::Light{ alloy::Color::red, alloy::ecs::LightType::POINT_LIGHT, 300 };
	entityManager.AddComponentData(entity2, static_cast<alloy::ecs::Component>(alloy::ecs::CoreComponent::LIGHT), reinterpret_cast<const alloy::ecs::IComponentData&>(entity2Light));
}

void WaterSimulationSystem::OnUpdate() {
	//Update Water
	timeBetweenUpdate_++;

	if (timeBetweenUpdate_ < timeBetweenUpdateInMS_) {
		return;
	}

	//Update water
	UpdateWater();

	//Fill tiles sprites
	for (auto i = 0; i < tilesToUpdate.size(); i++) {
		tilesToUpdate[i].SetSprite(tiles_[i]);
	}

	//TODO Automaticly update chunks when updating tiles
	tilemapManager_.UpdateChunk(tilesToUpdate, topLeft_, bottomRight_);

	timeBetweenUpdate_ = 0; //TODO Move it to FixedUpdate
}

math::ivec2 WaterSimulationSystem::IndexToCoords(const int index) const {
	return {index / tilemapSize_.x, index % tilemapSize_.x};
}

int WaterSimulationSystem::CoordsToIndex(const math::ivec2 coords) const {
	return coords.x * tilemapSize_.x + coords.y;
}

float WaterSimulationSystem::CalculateVerticalFlowValue(const float remainingLiquid, const int indexDest) {
	const float sum = remainingLiquid + waterPressure_[indexDest];

	if (sum <= maxPressure_) {
		return maxPressure_;
	}

	if (sum < 2.0f * maxPressure_ + maxCompression_) {
		return (maxPressure_ * maxPressure_ + sum * maxCompression_) / (maxPressure_ + maxCompression_);
	}
	
	return (sum + maxCompression_) / 2.0f;
}

void WaterSimulationSystem::UpdateWater() {
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
				if (flow > minFlow_)
					flow *= flowSpeed_;

				flow = std::max(flow, 0.0f);

				if (flow > std::min(maxFlow_, remainingPressure)) {
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
	for (int i = 0; i < diffs.size(); i++) {
		waterPressure_[i] += diffs[i];
	}

	float totalPressure = 0;
	for (auto index = 0; index < waterPressure_.size(); index++) {
		if (tileStates_[index] == TileState::SOLID) continue;

		totalPressure += waterPressure_[index];

		if (waterPressure_[index] <= 0) {
			//Air
			tiles_[index] = freeTile_;
			tileStates_[index] = TileState::AIR;
		} else if (waterPressure_[index] <= maxPressure_ * 0.5f) {
			tiles_[index] = waterTile1_;
			tileStates_[index] = TileState::LIQUID;
		} else if (waterPressure_[index] <= maxPressure_) {
			tiles_[index] = waterTile2_;
			tileStates_[index] = TileState::LIQUID;
		} else if (waterPressure_[index] <= maxPressure_ + maxCompression_) {
			tiles_[index] = waterTile3_;
			tileStates_[index] = TileState::LIQUID;
		} else if (waterPressure_[index] <= maxPressure_ + 2 * maxCompression_) {
			tiles_[index] = waterTile4_;
			tileStates_[index] = TileState::LIQUID;
		} else if (waterPressure_[index] > maxPressure_ + 2 * maxCompression_) {
			tiles_[index] = waterTile5_;
			tileStates_[index] = TileState::LIQUID;
		}
	}
}

void WaterSimulationSystem::CellularStep() {
	std::vector<int> nextStep;
	nextStep.reserve(tiles_.size());
	nextStep.insert(nextStep.begin(), tiles_.begin(), tiles_.end());

	for (auto index = 0; index < tiles_.size(); index++) {
		const auto coords = IndexToCoords(index);

		int nbAliveNeighbors = 0;

		for (const auto neighborOffset : neighborOffset_) {
			const auto neighborCoords = coords + neighborOffset;

			//Check for each coords to be inside current tilemap
			if (neighborCoords.x < 0 || neighborCoords.y < 0 || neighborCoords.x >= tilemapSize_.x || neighborCoords.y
				>= tilemapSize_.y) {
				continue;
			}

			if (tiles_[CoordsToIndex(neighborCoords)] == freeTile_) {
				nbAliveNeighbors++;
			}
		}

		const auto currentStatus = tiles_[index];

		if (currentStatus == freeTile_ && (nbAliveNeighbors == 1 || nbAliveNeighbors >= 4)) {
			nextStep[index] = freeTile_;
		} else if (currentStatus == solidTile_ && nbAliveNeighbors >= 5) {
			nextStep[index] = freeTile_;
		} else {
			nextStep[index] = solidTile_;
		}
	}

	tiles_.clear();
	tiles_.insert(tiles_.begin(), nextStep.begin(), nextStep.end());
}

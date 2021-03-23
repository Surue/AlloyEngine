#pragma once

#include <vector>

#include <interface_component_manager.h>
#include <vector.h>

namespace alloy::ecs {
struct Position {	
	math::fvec2 position;
};

class PositionComponentManager : public IComponentManager<Position> {
public:
	void SetComponentData(EntityIndex entityIndex, const Position& componentData) override {
		while(entityIndex >= positions_.size()) {
			positions_.resize(positions_.size() * 2 + 1);
		}
		positions_[entityIndex] = componentData;
	}

	const Position& GetComponentData(EntityIndex entityIndex) const override {
		return positions_[entityIndex];
	}

private:
	std::vector<Position> positions_;
};
} // namespace alloy::ecs
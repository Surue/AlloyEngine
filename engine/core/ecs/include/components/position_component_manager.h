#pragma once

#include <vector>

#include <components/interface_component_manager.h>
#include <vector.h>

namespace alloy::ecs {
struct Position {	
	math::fvec2 position;

	static constexpr ComponentID GetComponentID() {
		return static_cast<ComponentID>(CoreComponentID::POSITION);
	}
};

class PositionComponentManager final : public IComponentManager<Position> {
public:
	void SetComponentData(const EntityIndex entityIndex, const Position& componentData) override {
		while(entityIndex >= positions_.size()) {
			positions_.resize(positions_.size() * 2 + 1);
		}
		positions_[entityIndex] = componentData;
	}

	const Position& GetComponentData(const EntityIndex entityIndex) const override {
		return positions_[entityIndex];
	}

private:
	std::vector<Position> positions_;
};
} // namespace alloy::ecs
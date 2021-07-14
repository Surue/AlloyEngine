#pragma once

#include <vector>

#include <components/interface_component_manager.h>
#include <components/component.h>
//TODO Not implemented yet

namespace alloy::ecs {
struct Sprite {
	std::string spriteName;

	static constexpr ComponentID GetComponentID() {
		return static_cast<ComponentID>(CoreComponentID::SPRITE);
	}
};

class Renderer2DComponentManager final : public IComponentManager<Sprite> {
public:
	void SetComponentData(const EntityIndex entityIndex, const Sprite& componentData) override {
		while (entityIndex >= sprites_.size()) {
			sprites_.resize(sprites_.size() * 2 + 1);
		}
		sprites_[entityIndex] = componentData;
	}

	const Sprite& GetComponentData(const EntityIndex entityIndex) const override {
		return sprites_[entityIndex];
	}

private:
	std::vector<Sprite> sprites_;
};
} // namespace alloy::ecs
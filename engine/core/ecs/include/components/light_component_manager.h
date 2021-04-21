#pragma once

#include <vector>

#include <components/interface_component_manager.h>
#include <color.h>

namespace alloy::ecs {
enum class LightType : uint8_t {
	POINT_LIGHT,
	AMBIENT_LIGHT
};

struct Light {
	Color color = Color::white;
	LightType light_type = LightType::POINT_LIGHT;
	float radius = 1.0f;

	static constexpr ComponentID GetComponentID() {
		return static_cast<ComponentID>(CoreComponentID::LIGHT);
	}
};

class LightComponentManager : public IComponentManager<Light> {
public:
	void SetComponentData(const EntityIndex entityIndex, const Light& componentData) override {
		while (entityIndex >= lights_.size()) {
			lights_.resize(lights_.size() * 2 + 1);
		}
		lights_[entityIndex] = componentData;
	}

	const Light& GetComponentData(const EntityIndex entityIndex) const override {
		return lights_[entityIndex];
	}

private:
	std::vector<Light> lights_;
};
} // namespace alloy::ecs
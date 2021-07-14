#pragma once

#include <vector>

#include <components/interface_component_manager.h>
#include <components/component.h>
#include <color.h>

namespace alloy::ecs{

enum class Renderer2DShape : uint8_t {
	SQUARE = 0,
	CIRCLE
};

struct Renderer2D {
	Color color = Color::white;
	Renderer2DShape shape = Renderer2DShape::SQUARE;
	
	static constexpr ComponentID GetComponentID() {
		return static_cast<ComponentID>(CoreComponentID::RENDERER_2D);
	}
};

class Renderer2DComponentManager final : public IComponentManager<Renderer2D> {
public:
	void SetComponentData(const EntityIndex entityIndex, const Renderer2D& componentData) override {
		while (entityIndex >= renderers2d_.size()) {
			renderers2d_.resize(renderers2d_.size() * 2 + 1);
		}
		renderers2d_[entityIndex] = componentData;
	}

	const Renderer2D& GetComponentData(const EntityIndex entityIndex) const override {
		return renderers2d_[entityIndex];
	}

private:
	std::vector<Renderer2D> renderers2d_;
};
} // namespace alloy::ecs
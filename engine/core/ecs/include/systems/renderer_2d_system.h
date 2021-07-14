#pragma once

#include <systems/system.h>
#include <renderer_2d/renderer_2d.h>

namespace alloy {
class Renderer2DSystem : public ecs::System {
public:
	Renderer2DSystem(graphics::Renderer2D& renderer2d) :
		System({ ecs::SystemExecutionFlags::INIT, ecs::SystemExecutionFlags::UPDATE }),
		renderer2d_(renderer2d){}

	void OnInit() override;

	void OnUpdate() override;

private:
	graphics::Renderer2D& renderer2d_;
};
} // namespace alloy

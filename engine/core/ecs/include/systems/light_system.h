#pragma once

#include <systems/system.h>
#include <lights/light_manager.h>

namespace alloy {
class LightSystem : public ecs::System {
public:
	LightSystem(graphics::LightManager& lightManager) :
		System({ ecs::SystemExecutionFlags::INIT, ecs::SystemExecutionFlags::UPDATE }),
		lightManager_(lightManager){}

	void OnInit() override;

	void OnUpdate() override;

private:
	graphics::LightManager& lightManager_;
};
} // namespace alloy

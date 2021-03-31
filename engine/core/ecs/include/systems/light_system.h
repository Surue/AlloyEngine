#pragma once

#include "system.h"

namespace alloy {
class LightSystem : public ecs::System {
public:
	LightSystem() :
		System({ ecs::SystemExecutionFlags::INIT, ecs::SystemExecutionFlags::UPDATE }){}

	void OnInit() override;

	void OnUpdate() override;
};
} // namespace alloy

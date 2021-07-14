#pragma once
#include <systems/system.h>

class PlanetsSystem : public alloy::ecs::System {
public:
	PlanetsSystem() : System({alloy::ecs::SystemExecutionFlags::INIT, alloy::ecs::SystemExecutionFlags::INIT}) {
		
	}

	void OnInit() override;

	void OnUpdate() override;

private:

	const int nbPlanets_ = 500;
};

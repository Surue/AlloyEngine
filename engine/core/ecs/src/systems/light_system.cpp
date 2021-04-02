#include <systems/light_system.h>

#include <log.h>


#include "input_manager.h"
#include "lights/light_manager.h"

namespace alloy {

void LightSystem::OnInit() {
	//debug::Log("OnInit");
}

void LightSystem::OnUpdate() {
	//debug::Log("OnUpdate");
	auto& lightManager = ServiceLocator::Get<graphics::LightManager>();
	/*
	 * 1. Get all entities with LIGHT & POSITION
	 * 2. Send them to the LightManager to draw them
	 */

	//auto entities = entityManager_.GetEntities
	
	//graphics::ServiceLightManager::Get().Draw();
}
} // namespace alloy
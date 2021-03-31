#include <systems/light_system.h>

#include <log.h>

#include "lights/light_manager.h"

namespace alloy {

void LightSystem::OnInit() {
	debug::Log("OnInit");
}

void LightSystem::OnUpdate() {
	debug::Log("OnUpdate");
	//graphics::ServiceLightManager::Get().Draw();
}
} // namespace alloy
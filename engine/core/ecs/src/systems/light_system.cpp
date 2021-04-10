#include <systems/light_system.h>

#include <log.h>


#include <input_manager.h>
#include <lights/light_manager.h>
#include <entity_manager.h>

namespace alloy {

void LightSystem::OnInit() {
	//debug::Log("OnInit");
}

void LightSystem::OnUpdate() {
	//debug::Log("OnUpdate");
	//auto& lightManager = ServiceLocator::Get<graphics::LightManager>();
	/*
	 * 1. Get all entities with LIGHT & POSITION
	 * 2. Send them to the LightManager to draw them
	 */

	auto entities = ServiceLocator::Get<ecs::EntityManager>().GetEntities({ static_cast<ecs::Component>(ecs::CoreComponent::POSITION), static_cast<ecs::Component>(ecs::CoreComponent::LIGHT)});

	graphics::PointLight spotLight1{
		Color::fuchsia,
		{300, 300},
		300
	};

	graphics::PointLight spotLight2{
		Color::red,
		{300, 150},
		300
	};
	std::vector<graphics::PointLight> pointsLights;
	pointsLights.push_back(spotLight1);
	pointsLights.push_back(spotLight2);
	
	lightManager_.AddPointLightsToDraw(pointsLights);
}
} // namespace alloy
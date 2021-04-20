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

	//TODO Find a solution to have READ_ONLY components => Some optimization are certainly possible
	auto& entityManager = ServiceLocator::Get<ecs::EntityManager>();
	auto entities = entityManager.GetEntities({ static_cast<ecs::Component>(ecs::CoreComponent::POSITION), static_cast<ecs::Component>(ecs::CoreComponent::LIGHT)});

	std::vector<graphics::PointLight> pointsLights;
	pointsLights.reserve(entities.size());
	
	for(int i = 0; i < entities.size(); i++) {
		const auto entityIndex = entities[i];

		const auto& position = entityManager.GetComponentData<ecs::Position>(entityIndex, static_cast<ecs::Component>(ecs::CoreComponent::POSITION));
		const auto& light = entityManager.GetComponentData<ecs::Light>(entityIndex, static_cast<ecs::Component>(ecs::CoreComponent::LIGHT));

		graphics::PointLight spotLight{
		light.color,
		position.position,
		light.radius
		};

		pointsLights.emplace_back(spotLight);
	}

	
	lightManager_.AddPointLightsToDraw(pointsLights);
}
} // namespace alloy
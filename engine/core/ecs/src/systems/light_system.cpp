#include <systems/light_system.h>

#include <log.h>

#include <input_manager.h>
#include <lights/light_manager.h>
#include <entity_manager.h>

namespace alloy {

void LightSystem::OnInit() {}

void LightSystem::OnUpdate() {
	auto& entityManager = ServiceLocator::Get<ecs::EntityManager>();
	auto entities = entityManager.GetEntities({ static_cast<ecs::ComponentID>(ecs::CoreComponentID::POSITION), static_cast<ecs::ComponentID>(ecs::CoreComponentID::LIGHT)});

	std::vector<graphics::PointLight> pointsLights;
	pointsLights.reserve(entities.size());
	
	for(size_t i = 0; i < entities.size(); i++) {
		const auto entityIndex = entities[i];

		const auto& position = entityManager.GetComponentData<ecs::Position>(entityIndex);
		const auto& light = entityManager.GetComponentData<ecs::Light>(entityIndex);

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
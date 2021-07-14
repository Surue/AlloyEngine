#include <planets_system.h>

#include <entity_manager.h>
#include <service_locator.h>
#include <random.h>

void PlanetsSystem::OnInit() {
	auto& entityManager = alloy::ServiceLocator::Get<alloy::ecs::EntityManager>();

	//TODO Get size from window
	const auto maxX = 600.0f;
	const auto maxY = 600.0f;
	
	for(int i = 0; i < nbPlanets_; i++) {
		const auto entityIndex = entityManager.CreateEntity();

		entityManager.AddComponentData<alloy::ecs::Position>(entityIndex, alloy::ecs::Position{ {math::RandomRange(0.0f, maxX), math::RandomRange(0.0f, maxY)} });
		entityManager.AddComponentData<alloy::ecs::Renderer2D>(entityIndex, alloy::ecs::Renderer2D{alloy::Color::white, alloy::ecs::Renderer2DShape::CIRCLE });
	}
}

void PlanetsSystem::OnUpdate() { }

#include <planets_system.h>


#include <entity_manager.h>
#include <service_locator.h>

void PlanetsSystem::OnInit() {
	auto& entityManager = alloy::ServiceLocator::Get<alloy::ecs::EntityManager>();

	int maxX = 600;
	int maxY = 600;
	
	for(int i = 0; i < 500; i++) {
		const auto entityIndex = entityManager.CreateEntity();

		entityManager.AddComponentData<alloy::ecs::Position>(entityIndex, alloy::ecs::Position{ {10, 10} });
	}
}

void PlanetsSystem::OnUpdate() { }

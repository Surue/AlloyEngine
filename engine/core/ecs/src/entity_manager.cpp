#include <entity_manager.h>

namespace alloy::ecs {

void EntityManager::AddComponent(const EntityIndex entityIndex, const Component component) {
	entities_[entityIndex].set(component);
}

void EntityManager::RemoveComponent(const EntityIndex entityIndex, const Component component) {
	entities_[entityIndex].reset(component);
}

bool EntityManager::HasComponent(const EntityIndex entityIndex, const Component component) {
	return entities_[entityIndex].test(component);
}
} // namespace alloy::ecs

#include <entity_handle.h>

#include <entity_manager.h>

namespace alloy::ecs {

void EntityHandle::AddComponent(const Component component) const {
	entityManager_.AddComponent(entityIndex_, component);
}

void EntityHandle::RemoveComponent(const Component component) const {
	entityManager_.RemoveComponent(entityIndex_, component);
}

bool EntityHandle::HasComponent(const Component component) const {
	return entityManager_.HasComponent(entityIndex_, component);
}
} // namespace alloy::ecs
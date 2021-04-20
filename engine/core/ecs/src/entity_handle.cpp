#include <entity_handle.h>

namespace alloy::ecs {

void EntityHandle::AddComponent(const ComponentID component) {
	entity_.set(component);
}

void EntityHandle::RemoveComponent(const ComponentID component) {
	entity_.reset(component);
}

bool EntityHandle::HasComponent(const ComponentID component) const {
	return entity_.test(component);
}

Entity EntityHandle::GetEntity() const {
	return entity_;
}
} // namespace alloy::ecs

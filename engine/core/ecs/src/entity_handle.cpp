#include <entity_handle.h>

namespace alloy::ecs {

void EntityHandle::AddComponent(const Component component) {
	entity_.set(component);
}

void EntityHandle::RemoveComponent(const Component component) {
	entity_.reset(component);
}

bool EntityHandle::HasComponent(const Component component) const {
	return entity_.test(component);
}

Entity EntityHandle::GetEntity() const {
	return entity_;
}
} // namespace alloy::ecs

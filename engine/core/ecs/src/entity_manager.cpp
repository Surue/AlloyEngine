#include <entity_manager.h>

#include <component.h>

namespace alloy::ecs {

EntityIndex EntityManager::CreateEntity() {
	const auto entityIndex = firstNonInstantiatedEntityIndex_;

	//Check for next free entity
	for (auto index = firstNonInstantiatedEntityIndex_ + 1; index < entities_.size(); index++) {
		if (!HasComponent(index, static_cast<Component>(CoreComponent::INSTANTIATED_FLAG))) {
			firstNonInstantiatedEntityIndex_ = index;
			break;
		}
	}

	//Resize number of entity if no more non-instantiated entities
	if (firstNonInstantiatedEntityIndex_ == entityIndex) {
		firstNonInstantiatedEntityIndex_ = entities_.size();

		entities_.resize(entities_.size() * 2);
	}

	//Set the entity as instantiated
	AddComponent(entityIndex, static_cast<Component>(CoreComponent::INSTANTIATED_FLAG));

	return entityIndex;
}

void EntityManager::DestroyEntity(const EntityIndex entityIndex) {
	ClearEntity(entityIndex);

	//Reset first non instantiated entity index if needed
	if (entityIndex < firstNonInstantiatedEntityIndex_) {
		firstNonInstantiatedEntityIndex_ = entityIndex;
	}

	//TODO Ping archetype that listen to this component
}

void EntityManager::AddComponent(const EntityIndex entityIndex, const Component component) {
	entities_[entityIndex].set(component);

	//TODO Ping archetype that listen to this component
}

void EntityManager::AddComponentData(const EntityIndex entityIndex, const Component component,
                                     const IComponentData& componentData) {
	entities_[entityIndex].set(component);

	//TODO Find a compile time solution
	switch(component) {
		case static_cast<Component>(CoreComponent::POSITION) :
			positionComponentManager_.SetComponentData(entityIndex, reinterpret_cast<const Position&>(componentData));
		break;
	default: ;
	}

	//TODO Ping archetype that listen to this component
}

void EntityManager::RemoveComponent(const EntityIndex entityIndex, const Component component) {
	entities_[entityIndex].reset(component);

	//TODO Ping archetype that listen to this component
}

bool EntityManager::HasComponent(EntityIndex entityIndex, Component component) const {
	return entities_[entityIndex].test(component);
}
} // namespace alloy::ecs

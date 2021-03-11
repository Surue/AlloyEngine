#pragma once

#include <entity.h>

#include <component.h>

namespace alloy::ecs {

//Prototypes
class EntityManager;

class EntityHandle {
friend class EntityManager;
public:

	void AddComponent(Component component) const;

	void RemoveComponent(Component component) const;

	bool HasComponent(Component component) const;

private:
	EntityHandle(EntityManager& entityManager, EntityIndex entityIndex) : entityIndex_(entityIndex), entityManager_(entityManager) {

	}
	
	EntityIndex entityIndex_;
	
	EntityManager& entityManager_;
};
} // namespace alloy::ecs

#pragma once

#include <entity.h>

#include <component.h>

namespace alloy::ecs {

//Prototypes
class EntityManagerBase;

class EntityHandle {
friend class EntityManagerBase;
friend class EntityManager;
friend class EntityManagerNull;
public:

	void AddComponent(Component component) const;

	void RemoveComponent(Component component) const;

	bool HasComponent(Component component) const;

	Entity GetEntity() const;

	EntityIndex GetEntityIndex() const;

private:
	EntityHandle(EntityManagerBase& entityManager, EntityIndex entityIndex) : entityIndex_(entityIndex), entityManager_(entityManager) {

	}
	
	EntityIndex entityIndex_;
	
	EntityManagerBase& entityManager_;
};
} // namespace alloy::ecs

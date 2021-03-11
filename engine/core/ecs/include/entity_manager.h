#pragma once
#include <vector>

#include <entity_handle.h>

namespace alloy::ecs {
class EntityManager {
friend class EntityHandle;
public:
	EntityManager() {
		
	}

	~EntityManager() = default;

	EntityHandle CreateEntity() {
		
	}

private:
	void AddComponent(EntityIndex entityIndex, Component component);

	void RemoveComponent(EntityIndex entityIndex, Component component);

	bool HasComponent(EntityIndex entityIndex, Component component);
	
	std::vector<Entity> entities_;
};
} // namespace alloy::ecs

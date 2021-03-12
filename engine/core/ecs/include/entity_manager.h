#pragma once
#include <vector>

#include <entity_handle.h>

namespace alloy::ecs {
class EntityManager {
friend class EntityHandle;
public:
	EntityManager() {
		nextEntity_ = 0;
		entities_ = std::vector<Entity>(1);
	}

	~EntityManager() = default;

	EntityHandle CreateEntity() {
		if(nextEntity_ >= entities_.size()) {
			entities_.resize(entities_.size() * 2);
		}

		return EntityHandle(*this, nextEntity_++);
	}

	Entity GetEntity(EntityIndex entityIndex) {
		return entities_[entityIndex];
	}

private:
	void AddComponent(EntityIndex entityIndex, Component component);

	void RemoveComponent(EntityIndex entityIndex, Component component);

	bool HasComponent(EntityIndex entityIndex, Component component);
	
	std::vector<Entity> entities_;

	EntityIndex nextEntity_;
};
} // namespace alloy::ecs

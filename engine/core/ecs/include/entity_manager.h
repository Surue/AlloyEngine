#pragma once
#include <vector>

#include <entity_handle.h>

#include <service_locator.h>

namespace alloy::ecs {
class EntityManagerBase {
friend class EntityHandle;
public:
	virtual EntityHandle CreateEntity() = 0;

	virtual Entity GetEntity(EntityIndex entityIndex) = 0;

private:
	virtual void AddComponent(EntityIndex entityIndex, Component component) = 0;

	virtual void RemoveComponent(EntityIndex entityIndex, Component component) = 0;

	virtual bool HasComponent(EntityIndex entityIndex, Component component) = 0;
};

class EntityManagerNull : public EntityManagerBase {
friend class EntityHandle;
public:
	EntityHandle CreateEntity() override {
		return EntityHandle(*this, 0);
	}
	Entity GetEntity(EntityIndex entityIndex) override {
		return 0;
	}

private:
	void AddComponent(EntityIndex entityIndex, Component component) override{}
	void RemoveComponent(EntityIndex entityIndex, Component component) override{}
	bool HasComponent(EntityIndex entityIndex, Component component) override { return false; }
};

class EntityManager : public EntityManagerBase{
friend class EntityHandle;
public:
	EntityManager() {
		nextEntity_ = 0;
		entities_ = std::vector<Entity>(1);
	}

	~EntityManager() = default;

	EntityHandle CreateEntity() override {
		if(nextEntity_ >= entities_.size()) {
			entities_.resize(entities_.size() * 2);
		}

		return EntityHandle(*this, nextEntity_++);
	}

	Entity GetEntity(EntityIndex entityIndex) override {
		return entities_[entityIndex];
	}

private:
	void AddComponent(EntityIndex entityIndex, Component component) override;

	void RemoveComponent(EntityIndex entityIndex, Component component) override;

	bool HasComponent(EntityIndex entityIndex, Component component) override;
	
	std::vector<Entity> entities_;

	EntityIndex nextEntity_;
};

using ServiceEntityManager = ServiceLocator<EntityManagerBase, EntityManagerNull>;
} // namespace alloy::ecs

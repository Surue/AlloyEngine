#pragma once
#include <vector>

#include <entity_handle.h>

#include <service_locator.h>

namespace alloy::ecs {
class EntityManagerBase {
public:
	
	/**
	 * \brief Create an entity
	 * \return 
	 */
	virtual EntityIndex CreateEntity() = 0;
	
	/**
	 * \brief Destroy an entity and remove all its components
	 * \param entityIndex 
	 */
	virtual void DestroyEntity(EntityIndex entityIndex) = 0;

	/**
	 * \brief Add a component to the given entityIndex
	 * \param entityIndex 
	 * \param component 
	 */
	virtual void AddComponent(EntityIndex entityIndex, const Component component) = 0;
	
	/**
	 * \brief Add a component and its data to an entity
	 * \param entityIndex 
	 * \param component 
	 * \param componentData 
	 */
	virtual void AddComponentData(EntityIndex entityIndex, const Component component, const IComponentData& componentData) = 0;

	/**
	 * \brief Remove a component to an entity
	 * \param entityIndex 
	 * \param component 
	 */
	virtual void RemoveComponent(EntityIndex entityIndex, const Component component) = 0;

	/**
	 * \brief Check if the entity has the given component
	 * \param entityIndex 
	 * \param component 
	 * \return 
	 */
	virtual bool HasComponent(EntityIndex entityIndex, const Component component) = 0;
};

class EntityManagerNull : public EntityManagerBase {
public:
	EntityIndex CreateEntity() override { return -1; }

	void DestroyEntity(EntityIndex entityIndex) override {}
	
	void AddComponent(EntityIndex entityIndex, const Component component) override{}
	
	void AddComponentData(EntityIndex entityIndex, const Component component, const IComponentData& componentData) override{}
	void RemoveComponent(EntityIndex entityIndex, const Component component) override{}
	bool HasComponent(EntityIndex entityIndex, const Component component) override { return false; }
};

/*
 * TODO Archetype is a dynamic thing that are listen by system
 */

class EntityManager : public EntityManagerBase{
public:
	EntityManager() {
		firstNonInstantiatedEntityIndex_ = 0;
		entities_ = std::vector<Entity>(1);
	}

	~EntityManager() = default;

	EntityIndex CreateEntity() override;

	void DestroyEntity(const EntityIndex entityIndex) override;

	void AddComponent(const EntityIndex entityIndex, const Component component) override;

	void AddComponentData(const EntityIndex entityIndex, const Component component,
	                      const IComponentData& componentData) override;

	void RemoveComponent(const EntityIndex entityIndex, const Component component) override;

	bool HasComponent(const EntityIndex entityIndex, const Component component) override;

private:

	void ClearEntity(const EntityIndex entityIndex) {
		entities_[entityIndex].reset();
	}
	
	std::vector<Entity> entities_;

	EntityIndex firstNonInstantiatedEntityIndex_;
};

using ServiceEntityManager = ServiceLocator<EntityManagerBase, EntityManagerNull>;
} // namespace alloy::ecs

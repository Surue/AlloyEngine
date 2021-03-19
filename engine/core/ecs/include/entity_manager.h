#pragma once
#include <vector>

#include <service_locator.h>
#include <position_component_manager.h>
#include <component.h>

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
	virtual void AddComponent(EntityIndex entityIndex, Component component) = 0;
	
	/**
	 * \brief Add a component and its data to an entity
	 * \param entityIndex 
	 * \param component 
	 * \param componentData 
	 */
	virtual void AddComponentData(EntityIndex entityIndex, Component component, const IComponentData& componentData) = 0;

	/**
	 * \brief Remove a component to an entity
	 * \param entityIndex 
	 * \param component 
	 */
	virtual void RemoveComponent(EntityIndex entityIndex, Component component) = 0;

	/**
	 * \brief Check if the entity has the given component
	 * \param entityIndex 
	 * \param component 
	 * \return 
	 */
	virtual bool HasComponent(EntityIndex entityIndex, Component component) = 0;

	virtual const IComponentData& GetComponentData(EntityIndex entityIndex, Component component) const = 0;
};

class EntityManagerNull : public EntityManagerBase {
public:
	EntityIndex CreateEntity() override { return -1; }

	void DestroyEntity(EntityIndex entityIndex) override {}
	
	void AddComponent(EntityIndex entityIndex, const Component component) override{}
	
	void AddComponentData(EntityIndex entityIndex, const Component component, const IComponentData& componentData) override{}
	void RemoveComponent(EntityIndex entityIndex, const Component component) override{}
	bool HasComponent(EntityIndex entityIndex, const Component component) override { return false; }
	const IComponentData& GetComponentData(EntityIndex entityIndex, Component component) const override {
		IComponentData i;
		return i;
	}
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

	void DestroyEntity(EntityIndex entityIndex) override;

	void AddComponent(EntityIndex entityIndex, Component component) override;

	void AddComponentData(EntityIndex entityIndex, Component component,
	                      const IComponentData& componentData) override;

	void RemoveComponent(EntityIndex entityIndex, Component component) override;

	bool HasComponent(EntityIndex entityIndex, Component component) override;

	const IComponentData& GetComponentData(EntityIndex entityIndex, Component component) const override;
private:

	void ClearEntity(const EntityIndex entityIndex) {
		entities_[entityIndex].reset();
	}

	std::vector<Entity> entities_;

	EntityIndex firstNonInstantiatedEntityIndex_;

	PositionComponentManager positionComponentManager_;
};

using ServiceEntityManager = ServiceLocator<EntityManagerBase, EntityManagerNull>;
} // namespace alloy::ecs

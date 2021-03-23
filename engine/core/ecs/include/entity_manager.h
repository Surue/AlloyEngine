#pragma once
#include <vector>

#include <position_component_manager.h>
#include <component.h>

namespace alloy::ecs {
class EntityManager {
public:

	EntityManager() {
		firstNonInstantiatedEntityIndex_ = 0;
	    entities_ = std::vector<Entity>(1);
	}
	
	/**
	 * \brief Create an entity
	 * \return 
	 */
	EntityIndex CreateEntity();
	
	/**
	 * \brief Destroy an entity and remove all its components
	 * \param entityIndex 
	 */
	void DestroyEntity(EntityIndex entityIndex);

	/**
	 * \brief Add a component to the given entityIndex
	 * \param entityIndex 
	 * \param component 
	 */
	void AddComponent(EntityIndex entityIndex, Component component);
	
	/**
	 * \brief Add a component and its data to an entity
	 * \param entityIndex 
	 * \param component 
	 * \param componentData 
	 */
	void AddComponentData(EntityIndex entityIndex, Component component, const IComponentData& componentData);

	/**
	 * \brief Remove a component to an entity
	 * \param entityIndex 
	 * \param component 
	 */
	void RemoveComponent(EntityIndex entityIndex, Component component);

	/**
	 * \brief Check if the entity has the given component
	 * \param entityIndex 
	 * \param component 
	 * \return 
	 */
	bool HasComponent(EntityIndex entityIndex, Component component) const;

	template<typename T>
	const T& GetComponentData(EntityIndex entityIndex, Component component) const {
		switch (component) {
			case static_cast<Component>(CoreComponent::POSITION) :
				return positionComponentManager_.GetComponentData(entityIndex);
			default:;
		}
	}

private:
	void ClearEntity(const EntityIndex entityIndex) {
		entities_[entityIndex].reset();
	}

	std::vector<Entity> entities_;

	EntityIndex firstNonInstantiatedEntityIndex_;

	PositionComponentManager positionComponentManager_;
};
} // namespace alloy::ecs

#pragma once
#include <vector>

#include <components/Component.h>
#include <components/light_component_manager.h>
#include <components/position_component_manager.h>
#include <service_locator.h>

namespace alloy::ecs {
	template <typename T>
	class HasGetComponentIndex
	{
	private:
		typedef char YesType[1];
		typedef char NoType[2];

		template <typename C> static YesType& test(decltype(&C::GetComponentID));
		template <typename C> static NoType& test(...);


	public:
		enum { value = sizeof(test<T>(0)) == sizeof(YesType) };
	};

class EntityManager : public IService {
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
	void AddComponent(EntityIndex entityIndex, ComponentID component);

	//TODO Not very optimize if the need is just to set the data if the component is already added to the entity
	/**
	 * \brief Add a component and its data to an entity
	 * \param entityIndex 
	 * \param componentData 
	 */
	template<typename T>
	void AddComponentData(EntityIndex entityIndex, const T& componentData) {
		static_assert(HasGetComponentIndex<T>::value, "T has to define a function called GetComponentID");
		entities_[entityIndex].set(T::GetComponentID());

		switch (T::GetComponentID()) {
			case static_cast<ComponentID>(CoreComponentID::POSITION) :
				positionComponentManager_.SetComponentData(entityIndex, (const Position&)componentData);
				break;
			case static_cast<ComponentID>(CoreComponentID::LIGHT) :
				lightComponentManager_.SetComponentData(entityIndex, (const Light&)componentData);
				break;
			default:;
		}

		//TODO 1.0 Ping archetype that listen to this component
	}

	/**
	 * \brief Remove a component to an entity
	 * \param entityIndex 
	 * \param component 
	 */
	void RemoveComponent(EntityIndex entityIndex, ComponentID component);

	/**
	 * \brief Check if the entity has the given component
	 * \param entityIndex 
	 * \param component 
	 * \return 
	 */
	bool HasComponent(EntityIndex entityIndex, ComponentID component) const;

	//TODO Add an index to the typename T to get the correct component manager, thus removing the need of the second parameter
	template<typename T>
	const T& GetComponentData(const EntityIndex entityIndex) const {
		static_assert(HasGetComponentIndex<T>::value, "T has to define a function called GetComponentID");
		
		switch (T::GetComponentID()) {
			case static_cast<ComponentID>(CoreComponentID::POSITION) :
				return (const T&)positionComponentManager_.GetComponentData(entityIndex);
			case static_cast<ComponentID>(CoreComponentID::LIGHT) :
				return (const T&)lightComponentManager_.GetComponentData(entityIndex);
			default:;
		}
	}

	std::vector<EntityIndex> GetEntities(const std::vector<ComponentID>& components) {
		std::vector<EntityIndex> entities;

		for(size_t i = 0; i < entities_.size(); i++) {
			//TODO Optimize
			bool hasAllComponents = true;
			for(int j = 0; j < components.size(); j++) {
				if(!HasComponent(i, components[j])) {
					hasAllComponents = false;
					break;
				}
			}

			//TODO optimize
			if(hasAllComponents) {
				entities.push_back(i);
			}
		}
		
		return entities;
	}

private:
	void ClearEntity(const EntityIndex entityIndex) {
		entities_[entityIndex].reset();
	}

	std::vector<Entity> entities_;

	EntityIndex firstNonInstantiatedEntityIndex_;

	PositionComponentManager positionComponentManager_;
	LightComponentManager lightComponentManager_;
};
} // namespace alloy::ecs

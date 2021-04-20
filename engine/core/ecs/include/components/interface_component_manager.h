#pragma once

#include <entity.h>

namespace alloy::ecs {

template<typename T>
class IComponentManager {
public:
	virtual void SetComponentData(EntityIndex entityIndex, const T& componentData) = 0;

	virtual const T& GetComponentData(EntityIndex entityIndex) const = 0;
};
}

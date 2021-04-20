#pragma once

#include <entity.h>

#include <components/Component.h>

namespace alloy::ecs {
class EntityHandle {
public:

	void AddComponent(ComponentID component);

	void RemoveComponent(ComponentID component);

	bool HasComponent(ComponentID component)const ;

	Entity GetEntity() const;

private:
	Entity entity_;
};
} // namespace alloy::ecs

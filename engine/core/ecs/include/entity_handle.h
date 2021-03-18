#pragma once

#include <entity.h>

#include <component.h>

namespace alloy::ecs {
class EntityHandle {
public:

	void AddComponent(Component component);

	void RemoveComponent(Component component);

	bool HasComponent(Component component)const ;

	Entity GetEntity() const;

private:
	Entity entity_;
};
} // namespace alloy::ecs

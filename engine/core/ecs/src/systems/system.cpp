#include <systems/system.h>

#include <entity_manager.h>

namespace alloy::ecs {

System::System(const std::vector<SystemExecutionFlags>& flags):
	entityManager_(ServiceLocator::Get<EntityManager>()) {
	for (const auto systemExecutionFlags : flags) {
		AddFlag(systemExecutionFlags);
	}
}
} //namespace alloy::ecs

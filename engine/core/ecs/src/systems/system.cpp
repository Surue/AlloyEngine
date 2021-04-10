#include <systems/system.h>

#include <entity_manager.h>

namespace alloy::ecs {

System::System(const std::vector<SystemExecutionFlags>& flags) {
	for (const auto systemExecutionFlags : flags) {
		AddFlag(systemExecutionFlags);
	}
}
} //namespace alloy::ecs

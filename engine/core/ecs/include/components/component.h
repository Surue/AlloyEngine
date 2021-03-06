#pragma once
#include <cstdint>

namespace alloy::ecs {
using ComponentID = uint64_t;

enum class CoreComponentID : ComponentID {
	INSTANTIATED_FLAG = 0,
	POSITION,
	LIGHT,
	LENGTH
};

} // namespace alloy::ecs

#pragma once
#include <cstdint>

namespace alloy::ecs {
using Component = uint64_t;

enum class CoreComponent : Component {
	INSTANTIATED_FLAG = 0,
	POSITION,
	LENGTH
};

struct IComponentData {
	
};
}

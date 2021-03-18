#pragma once
#include <cstdint>

namespace alloy::ecs {
struct IComponentData {};

using Component = uint64_t;

enum class CoreComponent : Component {
	INSTANTIATED_FLAG = 0,
	POSITION,
	LENGTH
};
}

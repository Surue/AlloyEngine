#pragma once
#include <cstdint>

namespace alloy::ecs {
using Component = uint64_t;

enum class CoreComponent : Component {
	POSITION = 0,
};
}

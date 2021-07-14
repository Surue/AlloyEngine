#pragma once

#include <color.h>
#include <vector.h>
#include <primitives/primitive.h>

namespace alloy::graphics {
struct DrawingInstruction2d {
	math::fvec2 position;
	math::fvec2 scale;

	Color color;

	PrimitiveType type;
};
} // namespace alloy::graphics

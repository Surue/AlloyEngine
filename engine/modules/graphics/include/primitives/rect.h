#pragma once

#include <SFML/Graphics.hpp>

#include <color.h>
#include <vector.h>

namespace alloy::graphics {
class Rect {
public:
	Rect(math::fvec2 size, math::fvec2 position, const Color& color);

	//TODO Remove out parameter
	void Draw(sf::RenderTarget& target) const;

private:
	math::fvec2 size_;
	math::fvec2 position_;
	Color color_;
};
} // namespace alloy::graphics

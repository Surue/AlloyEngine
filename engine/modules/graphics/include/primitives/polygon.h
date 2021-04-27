#pragma once

#include <SFML/Graphics.hpp>

#include <color.h>
#include <vector.h>

namespace alloy::graphics {
class Polygon {
public:
	Polygon(const std::vector<math::fvec2>& points, math::fvec2 position, const Color& color);

	//TODO Remove out parameter
	void Draw(sf::RenderTarget& target) const;

private:
	std::vector<math::fvec2> points_;
	math::fvec2 position_;
	Color color_;
};
} // namespace alloy::graphics

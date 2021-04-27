#pragma once

#include <SFML/Graphics.hpp>

#include <color.h>
#include <vector.h>

namespace alloy::graphics {
class Circle {
public:
	Circle(const float radius, const math::fvec2 position, const Color& color);

	//TODO Remove out parameter
	void Draw(sf::RenderTarget& target) const;

private:
	float radius_;
	math::fvec2 position_;
	Color color_;
};
} // namespace alloy::graphics

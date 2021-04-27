#pragma once
#include <SFML/Graphics/Color.hpp>

#include <color.h>

namespace alloy::graphics {
inline sf::Color ColorToSfColor(const Color& color) {
	return sf::Color(color.r, color.g, color.b, color.a);
}

inline Color SfColorToColor(const sf::Color& color) {
	return Color(color.r, color.g, color.b, color.a);
}

inline sf::Vector2f Fvec2ToSfVector2f(const math::fvec2 v) {
	return sf::Vector2f(v.x, v.y);
}
}

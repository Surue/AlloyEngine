#include <primitives/circle.h>

#include <sfml_graphics_extension.h>

namespace alloy::graphics {
Circle::Circle(const float radius, const math::fvec2 position, const Color& color):
	radius_(radius),
	position_(position),
	color_(color) {}

void Circle::Draw(sf::RenderTarget& target) const {
	sf::CircleShape shape;

	shape.setRadius(radius_);
	shape.setFillColor(ColorToSfColor(color_));
	shape.setPosition(position_.x, position_.y);
	shape.setPointCount(64);

	target.draw(shape);
}
} // namespace alloy::graphics

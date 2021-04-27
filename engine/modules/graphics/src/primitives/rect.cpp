#include <primitives/rect.h>

#include <sfml_graphics_extension.h>

namespace alloy::graphics {

Rect::Rect(const math::fvec2 size, const math::fvec2 position, const Color& color):
	size_(size),
	position_(position),
	color_(color) { }

void Rect::Draw(sf::RenderTarget& target) const {
	sf::RectangleShape shape;

	shape.setSize(Fvec2ToSfVector2f(size_));
	shape.setFillColor(ColorToSfColor(color_));
	shape.setPosition(position_.x, position_.y);

	target.draw(shape);
}
} // namespace alloy::graphics

#include <primitives/polygon.h>

#include <sfml_graphics_extension.h>

namespace alloy::graphics {
Polygon::Polygon(const std::vector<math::fvec2>& points, const math::fvec2 position, const Color& color):
	points_(points),
	position_(position),
	color_(color) { }

void Polygon::Draw(sf::RenderTarget& target) const {
	sf::ConvexShape shape;

	shape.setPointCount(points_.size());
	for (size_t i = 0; i < points_.size(); i++) {
		shape.setPoint(i, Fvec2ToSfVector2f(points_[i]));
	}
	shape.setFillColor(ColorToSfColor(color_));
	shape.setPosition(position_.x, position_.y);

	target.draw(shape);
}
} // namespace alloy::graphics

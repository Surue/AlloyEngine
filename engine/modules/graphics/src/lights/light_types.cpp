#include <lights/light_manager.h>

#include <glsl_extension.h>

namespace alloy::graphics {

PointLight::PointLight(const Color& color, const math::fvec2 position, const float radius, const float intensity):
	color(color),
	position(position),
	radius(radius),
	intensity(intensity) { }

void PointLight::Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) {
	sf::CircleShape circleShape;
	circleShape.setOrigin(radius, radius);
	circleShape.setRadius(radius);
	circleShape.setPosition(position.x, position.y);

	//TODO For each of those terms, use a const instead of writing a string => Create custom shader class
	shader.setUniform("lightColor", ColorToGlslVec4(color));
	shader.setUniform("falloff", Vec3ToGlslVec3(falloff_));
	shader.setUniform("intensity", intensity);
	shader.setUniform("iResolution", Vec2ToGlslVec2(renderTarget.getSize()));
	shader.setUniform("lightPos", sf::Glsl::Vec2(position.x, renderTarget.getSize().y - position.y)); //Windows's height - y <= SFML top left, OpenGl bottom left
	shader.setUniform("radius", radius);

	sf::RenderStates renderState;
	renderState.blendMode = sf::BlendAdd;
	renderState.shader = &shader;

	renderTarget.draw(circleShape, renderState);
}
}

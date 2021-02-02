#include <lights/light_manager.h>

namespace alloy::graphics {

void PointLight::Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) {
	sf::CircleShape circleShape;
	circleShape.setOrigin(radius, radius);
	circleShape.setRadius(radius);
	circleShape.setPosition(position.x, position.y);

	//TODO For each of those terms, use a const instead of writing a string 
	shader.setUniform("lightColor", sf::Glsl::Vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f)); //TODO Create a function
	shader.setUniform("falloff", sf::Glsl::Vec3(0.1f, 3.0f, 100.0f)); //TODO use a const
	shader.setUniform("intensity", intensity);
	shader.setUniform("iResolution", sf::Glsl::Vec2(renderTarget.getSize()));
	shader.setUniform("lightPos", sf::Glsl::Vec2(position.x, renderTarget.getSize().y - position.y)); //Windows's height - y <= SFML top left, OpenGl bottom left
	shader.setUniform("radius", radius);

	sf::RenderStates renderState;
	renderState.blendMode = sf::BlendAdd;
	renderState.shader = &shader;

	renderTarget.draw(circleShape, renderState);
}
}

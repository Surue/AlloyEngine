#include <lights/light_manager.h>

#include <log.h>

namespace alloy::graphics {

void LightManager::Draw(sf::RenderTarget& target) {
	lightMap_.clear(sf::Color(ambientLight_.color.r, ambientLight_.color.g, ambientLight_.color.b, ambientLight_.color.a));

	debug::Log(Color::aqua.ToString());

	sf::CircleShape circleShape;
	circleShape.setRadius(100);
	sf::Color color = sf::Color(255, 255, 255, 100);
	circleShape.setFillColor(color);
	circleShape.setPosition(100, 100);

	lightMap_.draw(circleShape, sf::BlendAdd);

	sf::CircleShape circleShape2;
	circleShape2.setRadius(100);
	sf::Color color2 = sf::Color(255, 255, 255, 100);
	circleShape2.setFillColor(color2);
	circleShape2.setPosition(200, 100);

	lightMap_.draw(circleShape2, sf::BlendAdd);

	lightMap_.display();
	sf::Sprite lightmapSprite = sf::Sprite(lightMap_.getTexture());
	target.draw(lightmapSprite, sf::BlendMultiply);
}
}

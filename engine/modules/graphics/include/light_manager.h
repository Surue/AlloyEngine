#pragma once
#include <SFML/Graphics.hpp>

#include <service_locator.h>

namespace alloy::graphics {
class LightManagerBase {
public:
	virtual void Init() = 0;

	virtual void Draw(sf::RenderTarget& target) = 0;
};

class LightManagerNull : public LightManagerBase {
public:
	void Init() override {}

	void Draw(sf::RenderTarget& target) override {}
};

class LightManager : public LightManagerBase {
public:
	LightManager() { 
		lightMap_.create(1000, 1000);
	}

	void Init() override {
		
	}

	void Draw(sf::RenderTarget& target) override {
		lightMap_.clear(sf::Color(10, 10, 10, 250));
	
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
private:
	sf::RenderTexture lightMap_;
};

using ServiceLightManager = ServiceLocator<LightManagerBase, LightManagerNull>;
}

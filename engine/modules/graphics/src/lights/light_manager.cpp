#include <lights/light_manager.h>

namespace alloy::graphics {

void LightManager::Draw(sf::RenderTarget& target) {
	ambientLight_.Draw(lightMap_);

	PointLight spotLight1{
		Color::fuchsia,
		{100, 100},
		100
	};
	spotLight1.color.a = 120;
	spotLight1.Draw(lightMap_);

	PointLight spotLight2{
		Color::red,
		{200, 100},
		100
	};

	spotLight2.color.a = 50;
	spotLight2.Draw(lightMap_);

	lightMap_.display();
	const sf::Sprite lightMapSprite = sf::Sprite(lightMap_.getTexture());
	target.draw(lightMapSprite, sf::BlendMultiply);
}
}

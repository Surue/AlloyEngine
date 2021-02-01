#include <lights/light_manager.h>

namespace alloy::graphics {

void LightManager::Draw(sf::RenderTarget& target) {
	ambientLight_.Draw(lightMap_, lightShader_);

	PointLight spotLight1{
		Color::fuchsia,
		{300, 300},
		300
	};
	spotLight1.Draw(lightMap_, lightShader_);

	PointLight spotLight2{
		Color::red,
		{300, 150},
		300
	};
	spotLight2.Draw(lightMap_, lightShader_);

	lightMap_.display();
	const sf::Sprite lightMapSprite = sf::Sprite(lightMap_.getTexture());
	target.draw(lightMapSprite, sf::BlendMultiply);
}
}

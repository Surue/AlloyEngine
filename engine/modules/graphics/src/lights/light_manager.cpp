#include <lights/light_manager.h>

namespace alloy::graphics {

void LightManager::Draw(sf::RenderTarget& target) {
	ambientLight_.Draw(lightMap_, lightShader_);

	PointLight spotLight1{
		Color::fuchsia,
		{300, 300},
		300
	};

	PointLight spotLight2{
		Color::red,
		{300, 150},
		300
	};
	pointsLightsToDraw_.push_back(spotLight1);
	pointsLightsToDraw_.push_back(spotLight2);
	
	for (auto& pointsLightsToDraw : pointsLightsToDraw_) {
		pointsLightsToDraw.Draw(lightMap_, lightShader_);
	}

	pointsLightsToDraw_.clear();

	lightMap_.display();
	const sf::Sprite lightMapSprite = sf::Sprite(lightMap_.getTexture());
	target.draw(lightMapSprite, sf::BlendMultiply);
}
} // namespace alloy::graphics

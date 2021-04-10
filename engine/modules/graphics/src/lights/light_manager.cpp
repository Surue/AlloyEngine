#include <lights/light_manager.h>

namespace alloy::graphics {

void LightManager::Draw(sf::RenderTarget& target) {
	ambientLight_.Draw(lightMap_, lightShader_);
	
	for (auto& pointsLightsToDraw : pointsLightsToDraw_) {
		pointsLightsToDraw.Draw(lightMap_, lightShader_);
	}

	pointsLightsToDraw_.clear();

	lightMap_.display();
	const sf::Sprite lightMapSprite = sf::Sprite(lightMap_.getTexture());
	target.draw(lightMapSprite, sf::BlendMultiply);
}
} // namespace alloy::graphics

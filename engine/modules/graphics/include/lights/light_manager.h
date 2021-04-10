#pragma once
#include <SFML/Graphics.hpp>

#include <lights/light_types.h>

namespace alloy::graphics {

struct LightManagerInitSettings {
	LightManagerInitSettings(const math::ivec2 windowSize) : windowSize(windowSize){}
	
	math::ivec2 windowSize;
};

class LightManager {
public:
	LightManager(const LightManagerInitSettings initSettings) {
		lightMap_.create(initSettings.windowSize.x, initSettings.windowSize.y);

		//TODO Load correctly shaders
		lightShader_.loadFromFile("../data/shaders/lights.frag", sf::Shader::Fragment);
	}

	void Init() {
		//TODO Use init by registering it
	}

	void Draw(sf::RenderTarget& target);

	void AddPointLightsToDraw(const std::vector<PointLight>& lights) {
		if (pointsLightsToDraw_.capacity() < pointsLightsToDraw_.size() + lights.size()) {
			pointsLightsToDraw_.reserve(pointsLightsToDraw_.size() + lights.size());
		}
		
		for (const auto& light : lights) {
			pointsLightsToDraw_.emplace_back(light);
		}
	}

	void UpdateAmbientLight(const AmbientLight& ambientLight) {
		ambientLight_ = ambientLight;
	}
private:
	sf::RenderTexture lightMap_;

	AmbientLight ambientLight_{Color::black};

	sf::Shader lightShader_;

	std::vector<PointLight> pointsLightsToDraw_;
};
} // namespace alloy::graphics

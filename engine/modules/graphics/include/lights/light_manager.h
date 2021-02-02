#pragma once
#include <SFML/Graphics.hpp>

#include <service_locator.h>
#include <lights/light_types.h>

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

struct LightManagerInitSettings {
	LightManagerInitSettings(const math::ivec2 windowSize) : windowSize(windowSize){}
	
	math::ivec2 windowSize;
};

class LightManager : public LightManagerBase {
public:
	LightManager(const LightManagerInitSettings initSettings) {
		lightMap_.create(initSettings.windowSize.x, initSettings.windowSize.y);

		//TODO Load correctly shaders
		lightShader_.loadFromFile("../data/shaders/lights.frag", sf::Shader::Fragment);
	}

	void Init() override {
		//TODO Use init by registering it
	}

	void Draw(sf::RenderTarget& target) override;
private:
	sf::RenderTexture lightMap_;

	AmbientLight ambientLight_{Color::black};

	sf::Shader lightShader_;
};

using ServiceLightManager = ServiceLocator<LightManagerBase, LightManagerNull>;
}

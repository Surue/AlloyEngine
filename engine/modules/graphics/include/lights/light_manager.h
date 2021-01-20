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

	void Draw(sf::RenderTarget& target) override;
private:
	sf::RenderTexture lightMap_;
};

using ServiceLightManager = ServiceLocator<LightManagerBase, LightManagerNull>;
}

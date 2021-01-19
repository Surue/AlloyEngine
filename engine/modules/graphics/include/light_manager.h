#pragma once
#include <SFML/Graphics.hpp>

#include <service_locator.h>

namespace alloy::graphics {
class LightManagerBase {
public:
	virtual void Init() = 0;

	virtual void Draw(sf::RenderTarget& target) const = 0;
};

class LightManagerNull : public LightManagerBase {
public:
	void Init() override {}

	void Draw(sf::RenderTarget& target) const override {}
};

class LightManager : public LightManagerBase {
public:
	LightManager() { 

	}

	void Init() override {
		
	}

	void Draw(sf::RenderTarget& target) const override {
		
	}
private:
	
};

using ServiceLightManager = ServiceLocator<LightManagerBase, LightManagerNull>;
}

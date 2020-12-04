#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

#include "graphics_engine.h"

namespace alloy {
namespace inputs {
class InputManager {
public:

	InputManager(graphics::GraphicsEngine& graphicsEngine) :
		graphicsEngine_(graphicsEngine){
		
	}

	void Init() {
		
	}

	void SetCallbackCloseWindow(const std::function<void()>& callback) {
		callbackCloseWindow_ = callback;
	}

	void Update() {
		sf::Event event;
		while (graphicsEngine_.GetWindow().PollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				callbackCloseWindow_();
		}
	}
private:
	const graphics::GraphicsEngine& graphicsEngine_;

	std::function<void()> callbackCloseWindow_;
};
}
}

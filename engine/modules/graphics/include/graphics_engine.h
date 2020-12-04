#pragma once

#include <memory>
#include <string_view>
#include <vector.h>

#include <SFML/Graphics.hpp>

namespace alloy {
namespace graphics {
struct GraphicsEngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class GraphicsEngine {
public:
	GraphicsEngine(GraphicsEngineInitSettings initSettings) {
		windowSize_ = initSettings.windowSize;
		windowName_ = initSettings.windowName;
	}

	void Init() {
		window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize_.x, windowSize_.y), &windowName_[0]);
	}

	void Update() {
		//Get events
		//TODO move it outside the graphics engine
		sf::Event event;
		while (window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_->close();
		}

		//Draw everything

		//Clear windows
		window_->clear();
		//Display
		window_->display();
	}

	bool IsWindowOpen() {
		return window_->isOpen();
	}
private:
	std::unique_ptr<sf::RenderWindow> window_;

	math::ivec2 windowSize_;
	std::string_view windowName_;
};
} //namespace graphics
} //namespace alloy

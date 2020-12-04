#pragma once

#include <window.h>

#include <SFML/Graphics.hpp>

#include <vector.h>

namespace alloy {
namespace graphics {
struct GraphicsEngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class GraphicsEngine {
public:
	GraphicsEngine(GraphicsEngineInitSettings initSettings) :
		window_({initSettings.windowName, initSettings.windowSize}){
	}

	void Init() {
		window_.Init();
	}

	void Update() {
		//Get events
		//TODO move it outside the graphics engine
		/*sf::Event event;
		while (window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.Close();
		}*/

		//Draw everything

		//Clear windows
		window_.Clear();
		//Display
		window_.Display();
	}

	bool IsWindowOpen() {
		return window_.IsOpen();
	}
private:
	Window window_;
};
} //namespace graphics
} //namespace alloy

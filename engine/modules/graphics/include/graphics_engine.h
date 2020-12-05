#pragma once

#include <functional>
#include <window.h>

#include <SFML/Graphics.hpp>

#include <vector.h>

#include "texture.h"

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

	//TODO remove
	Texture texture;
	sf::Sprite sprite;
	
	void Init() {
		window_.Init();

		//TODO remove
		texture.Load("data/sprites/policeman.png");
		sprite.setTexture(texture.GetSfTexture());
	}


	void Update() {
		//Clear windows
		window_.Clear();
		
		//Draw everything

		window_.Draw(sprite);
		
		//Display
		window_.Display();
	}

	bool IsWindowOpen() {
		return window_.IsOpen();
	}

	const Window& GetWindow() const {
		return window_;
	}

	const std::function<void()> GetCallbackCloseWindow() const {
		return [this]() {window_.Close(); };
	}
private:
	Window window_;
};
} //namespace graphics
} //namespace alloy

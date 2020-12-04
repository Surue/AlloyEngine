#pragma once

#include <functional>
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
		//Draw everything

		//Clear windows
		window_.Clear();
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

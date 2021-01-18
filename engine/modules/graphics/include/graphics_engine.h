#pragma once

#include <functional>
#include <window.h>

#include <SFML/Graphics.hpp>

#include <vector.h>
#include <tilemap_manager.h>

namespace alloy {
namespace graphics {
struct GraphicsEngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class GraphicsEngine {
public:
	GraphicsEngine(const GraphicsEngineInitSettings& initSettings) :
		window_({initSettings.windowName, initSettings.windowSize}),
		tilemapManager_() {
		ServiceTilemapManager::Assign(&tilemapManager_);
	}

	void Init();

	void Update();

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

	TilemapManager tilemapManager_;
};
} //namespace graphics
} //namespace alloy

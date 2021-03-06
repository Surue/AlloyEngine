#pragma once


#include <functional>

#include <SFML/Graphics.hpp>

#include <window.h>
#include <vector.h>
#include <tilemap_manager.h>
#include <lights/light_manager.h>

namespace alloy::graphics {
struct GraphicsEngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class GraphicsEngine {
public:
	GraphicsEngine(const GraphicsEngineInitSettings& initSettings) :
		window_({initSettings.windowName, initSettings.windowSize}),
		lightManager_(LightManagerInitSettings{ initSettings.windowSize }){
	}

	void Init();

	void Update();

	bool IsWindowOpen() const {
		return window_.IsOpen();
	}

	const Window& GetWindow() const {
		return window_;
	}

	const std::function<void()> GetCallbackCloseWindow() const {
		return [this]() {window_.Close(); };
	}

	LightManager& GetLightManagerRef() {
		return lightManager_;
	}

	TilemapManager& GetTilemapManagerRef() {
		return tilemapManager_;
	}
private:
	Window window_;

	TilemapManager tilemapManager_;
	LightManager lightManager_;
};
}

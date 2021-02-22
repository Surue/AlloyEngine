#pragma once

#include <vector.h>
#include <graphics_engine.h>
#include <input_manager.h>

namespace alloy {
struct EngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class Engine {
public:
	explicit Engine(const EngineInitSettings& initSettings);

	void Init();

	void Run();

	void Destroy() {
		
	}

	void Shutdown() {
		
	}

	void AddCallbackUpdate(std::function<void()> callback);
private:
	bool isRunning_;
	graphics::GraphicsEngine graphicsEngine_;
	inputs::InputManager inputManager_;

	std::vector<std::function<void()>> callbackUpdate_;
};
} //namespace alloy

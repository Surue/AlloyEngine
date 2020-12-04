#pragma once

#include <string_view>
#include <vector.h>
#include <log.h>

#include <graphics_engine.h>

#include <input_manager.h>

namespace alloy {
struct EngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class Engine {
public:
	Engine(const EngineInitSettings& initSettings):
		isRunning_(false),
		graphicsEngine_(graphics::GraphicsEngineInitSettings{initSettings.windowName, initSettings.windowSize}),
		inputManager_(graphicsEngine_){
	}

	void Init() {
		graphicsEngine_.Init();
		inputManager_.Init();

		inputManager_.SetCallbackCloseWindow(graphicsEngine_.GetCallbackCloseWindow());
	}

	void Run() {
		isRunning_ = true;
		
        while (isRunning_)
        {
			//Update every systems
			graphicsEngine_.Update();
			inputManager_.Update();
        	
            if(!graphicsEngine_.IsWindowOpen()) {
				isRunning_ = false;
            }
        }
	}

	void Destroy() {
		
	}

	void Shutdown() {
		
	}
private:
	bool isRunning_;
	graphics::GraphicsEngine graphicsEngine_;
	inputs::InputManager inputManager_;
};
} //namespace alloy

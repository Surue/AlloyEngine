#pragma once

#include <string_view>
#include <vector.h>

#include <graphics_engine.h>

namespace alloy {
struct EngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class Engine {
public:
	Engine(const EngineInitSettings& initSettings):
		isRunning_(false),
		graphicsEngine_(graphics::GraphicsEngineInitSettings{initSettings.windowName, initSettings.windowSize}){
	}

	void Init() {
		graphicsEngine_.Init();
	}

	void Run() {
		isRunning_ = true;
		
        while (isRunning_)
        {
			//Update every systems
			graphicsEngine_.Update();
        	
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
};
} //namespace alloy

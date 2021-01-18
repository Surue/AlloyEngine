#pragma once

#include <string_view>
#include <vector.h>

#include <graphics_engine.h>

#include <input_manager.h>
#include <iostream>

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
	        for (const auto& callbackUpdate : callbackUpdate_) {
				callbackUpdate();
	        }
        	
			//Update every systems
			graphicsEngine_.Update();
			inputManager_.Update();

        	if(inputManager_.IsKeyDown(inputs::KeyCode::A)) {
				std::cout << "A is down\n";
        	}

			if (inputManager_.IsKeyHeld(inputs::KeyCode::A)) {
				std::cout << "A is held\n";
			}

			if (inputManager_.IsKeyUp(inputs::KeyCode::A)) {
				std::cout << "A is up\n";
			}
        	
            if(!graphicsEngine_.IsWindowOpen()) {
				isRunning_ = false;
            }
        }
	}

	void Destroy() {
		
	}

	void Shutdown() {
		
	}

	void AddCallbackUpdate(std::function<void()> callback) {
		if(callbackUpdate_.size() == callbackUpdate_.capacity()) {
			callbackUpdate_.reserve(callbackUpdate_.size() * 2 + 1);
		}

		callbackUpdate_.emplace_back(callback);
	}
private:
	bool isRunning_;
	graphics::GraphicsEngine graphicsEngine_;
	inputs::InputManager inputManager_;

	std::vector<std::function<void()>> callbackUpdate_;
};
} //namespace alloy

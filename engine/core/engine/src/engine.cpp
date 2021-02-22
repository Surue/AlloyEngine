#include <engine.h>

namespace alloy {

Engine::Engine(const EngineInitSettings& initSettings):
	isRunning_(false),
	graphicsEngine_(graphics::GraphicsEngineInitSettings{initSettings.windowName, initSettings.windowSize}),
	inputManager_(graphicsEngine_) {
	inputs::ServiceInputManager::Assign(&inputManager_);
}

void Engine::Init() {
	graphicsEngine_.Init();
	inputManager_.Init();

	inputManager_.SetCallbackCloseWindow(graphicsEngine_.GetCallbackCloseWindow());
}

void Engine::Run() {
	isRunning_ = true;

	while (isRunning_) {
		//Update every systems
		for (const auto& callbackUpdate : callbackUpdate_) {
			callbackUpdate();
		}

		//Update every systems
		graphicsEngine_.Update();
		inputManager_.Update();

		if (!graphicsEngine_.IsWindowOpen()) {
			isRunning_ = false;
		}
	}
}

void Engine::AddCallbackUpdate(std::function<void()> callback) {
	if (callbackUpdate_.size() == callbackUpdate_.capacity()) {
		callbackUpdate_.reserve(callbackUpdate_.size() * 2 + 1);
	}

	callbackUpdate_.emplace_back(callback);
}
}

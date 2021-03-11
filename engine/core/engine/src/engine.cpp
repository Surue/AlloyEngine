#include <engine.h>
#include <iostream>

namespace alloy {

Engine::Engine(const EngineInitSettings& initSettings):
	isRunning_(false),
	graphicsEngine_(graphics::GraphicsEngineInitSettings{initSettings.windowName, initSettings.windowSize}),
	inputManager_(graphicsEngine_) {
	inputs::ServiceInputManager::Assign(&inputManager_);

	//Move the following function into a another type of execution function
	graphicsEngine_.Init();
	inputManager_.Init();

	inputManager_.SetCallbackCloseWindow(graphicsEngine_.GetCallbackCloseWindow());
}

void Engine::Init() {
	//TODO Empty this callback's container to reacte to spawned object in runtime
	for (auto callback : callbackContainer_[(uint32_t)ecs::SystemExecutionFlags::INIT]) {
		callback();
	}
}

void Engine::Run() {
	isRunning_ = true;

	while (isRunning_) {
		//Update every systems
		for (auto callback : callbackContainer_[(uint32_t)ecs::SystemExecutionFlags::UPDATE]) {
			callback();
		}

		//Update every systems
		graphicsEngine_.Update();
		inputManager_.Update();

		if (!graphicsEngine_.IsWindowOpen()) {
			isRunning_ = false;
		}
	}
}

}

#pragma once

#include <array>

#include <vector.h>
#include <graphics_engine.h>
#include <input_manager.h>

#include "system.h"

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
		for (auto callback : callbackContainer_[(uint32_t)ecs::SystemExecutionFlags::DESTROY]) {
			callback();
		}
	}

	void Shutdown() {
		
	}

	void AddSystem(ecs::System& system) {
		systems_.push_back(&system);

		const auto& flags = systems_[systems_.size() - 1]->GetSystemFlag();

		for(int i = 0; i < flags.size(); i++) {
			if(flags.test(i)) {
				auto f = static_cast<ecs::SystemExecutionFlags>(i);
				
				if (callbackContainer_[static_cast<uint32_t>(f)].size() == callbackContainer_[static_cast<uint32_t>(f)].capacity()) {
					callbackContainer_[static_cast<uint32_t>(f)].reserve(callbackContainer_.size() * 2 + 1);
				}

				switch (f) {
				case ecs::SystemExecutionFlags::INIT:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([this]() { systems_[systems_.size() - 1]->OnInit(); });
					break;
				case ecs::SystemExecutionFlags::UPDATE:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([this]() { systems_[systems_.size() - 1]->OnUpdate(); });
					break;
				case ecs::SystemExecutionFlags::DRAW:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([this]() { systems_[systems_.size() - 1]->OnDraw(); });
					break;
				case ecs::SystemExecutionFlags::DESTROY:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([this]() { systems_[systems_.size() - 1]->OnDestroy(); });
					break;
				default:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([]() {});
					break;
				}
			}
		}
	}
private:
	bool isRunning_;
	graphics::GraphicsEngine graphicsEngine_;
	inputs::InputManager inputManager_;

	std::vector<ecs::System*> systems_;

	std::array<std::vector<std::function<void()>>, static_cast<size_t>(ecs::SystemExecutionFlags::LENGTH)> callbackContainer_;
};
} //namespace alloy

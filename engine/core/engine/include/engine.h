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

	void RegisterSystem(ecs::System& system) {
		const auto& flags = system.GetSystemFlag();

		for(int i = 0; i < flags.size(); i++) {
			if(flags.test(i)) {
				auto f = static_cast<ecs::SystemExecutionFlags>(i);
				
				if (callbackContainer_[static_cast<uint32_t>(f)].size() == callbackContainer_[static_cast<uint32_t>(f)].capacity()) {
					callbackContainer_[static_cast<uint32_t>(f)].reserve(callbackContainer_.size() * 2 + 1);
				}

				switch (f) {
				case ecs::SystemExecutionFlags::INIT:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([&system]() { system.OnInit(); });
					break;
				case ecs::SystemExecutionFlags::UPDATE:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([&system]() { system.OnUpdate(); });
					break;
				case ecs::SystemExecutionFlags::DRAW:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([&system]() { system.OnDraw(); });
					break;
				case ecs::SystemExecutionFlags::DESTROY:
					callbackContainer_[static_cast<uint32_t>(f)].emplace_back([&system]() { system.OnDestroy(); });
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

	std::array<std::vector<std::function<void()>>, static_cast<size_t>(ecs::SystemExecutionFlags::LENGTH)> callbackContainer_;
};
} //namespace alloy

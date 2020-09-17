#define SDL_MAIN_HANDLED

#include <devices/instance.h>
#include <devices/logical_device.h>
#include <window.h>

namespace alloy {
class Engine {
public:
	void Init() {
		window_.Init();
		instance_.Init(window_.GetVulkanExtensions());
		physicalDevice_.Init(instance_);
		logicalDevice_.Init(physicalDevice_);
	}

	void Destroy() {
		instance_.Destroy();
		window_.Destroy();
	}

	void Run() {
		SDL_Event e;
		bool quit = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN) {
					quit = true;
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					quit = true;
				}
			}
		}
	}
private:
	sdlwrapper::Window window_;
	vulkanwrapper::Instance instance_;
	vulkanwrapper::PhysicalDevice physicalDevice_;
	vulkanwrapper::LogicalDevice logicalDevice_;
};
}

int main() {
	alloy::Engine engine;
	engine.Init();
	engine.Run();
	engine.Destroy();

    return 0;
}

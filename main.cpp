#include <iostream>
#include <vector>
#include <vector.h>
#include <log.h>

#define SDL_MAIN_HANDLED

#include <devices/instance.h>
#include <window.h>

#include <vulkan/vulkan.h>

namespace alloy {
class Engine {
public:
	void Init() {
		window_.Init();
		instance.Init(window_.GetVulkanExtensions());
	}


	void Destroy() {
		instance.Destroy();
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
	vulkanwrapper::Instance instance;
};
}

int main() {
	alloy::Engine engine;
	engine.Init();
	engine.Run();
	engine.Destroy();

    return 0;
}

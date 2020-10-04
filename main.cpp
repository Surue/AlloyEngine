#define SDL_MAIN_HANDLED

#include <devices/instance.h>
#include <devices/logical_device.h>

#include <devices/window.h>

namespace alloy {
class Engine {
public:

	void Init() {
		window_.Init();
		instance_.Init(window_.GetVulkanExtensions());
		physicalDevice_.Init(instance_);
		logicalDevice_.Init(physicalDevice_);

		//TODO(@Nico) Refactor the creation of the surface
		window_.CreateVulkanSurface(instance_, surface_);
	}

	void Destroy() {
		surface_.Destroy(&instance_);
		logicalDevice_.Destroy();
		physicalDevice_.Destroy();
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
	graphics::Window window_;
	vulkanwrapper::Instance instance_;
	vulkanwrapper::PhysicalDevice physicalDevice_;
	vulkanwrapper::LogicalDevice logicalDevice_;
	vulkanwrapper::Surface surface_;
};
}

int main() {
	alloy::Engine engine;
	engine.Init();
	engine.Run();
	engine.Destroy();

    return 0;
}

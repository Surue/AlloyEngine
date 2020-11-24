#pragma once

#define USE_SDL2
#include "../../../../wrappers/sdl/include/sdl_window.h"
#include "../../../../wrappers/vulkan/include/devices/instance.h"
#include "../../../../wrappers/vulkan/include/devices/surface.h"
#include <devices/vulkan_window.h>

namespace alloy::graphics {
#ifdef USE_SDL2
class Window : public sdlwrapper::SDLWindow, public vulkanwrapper::IVulkanWindow {
public:
	Window() = default;
	
	std::vector<const char*> GetVulkanExtensions() const override {
		//SDL extensions
		uint32_t sdlExtensionCount = 0;
		SDL_Vulkan_GetInstanceExtensions(window_, &sdlExtensionCount, nullptr);
		std::vector<const char*> sdlExtension(sdlExtensionCount);
		SDL_Vulkan_GetInstanceExtensions(window_, &sdlExtensionCount, sdlExtension.data());

		return sdlExtension;
	}

	void CreateVulkanSurface(const vulkanwrapper::Instance& instance, vulkanwrapper::Surface& surface) const override {
		if(SDL_Vulkan_CreateSurface(window_, &instance, surface.GetSurface()) != SDL_TRUE) {
			//TODO add error log
		}
	}
private:
};
#endif
} //namespace alloy::graphics
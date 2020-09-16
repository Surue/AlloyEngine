#include <window.h>

namespace alloy::sdlwrapper {
bool Window::Init() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cerr << "SDL_Init Error: " + static_cast<std::string>(SDL_GetError()) << "\n";
		}

		window_ = SDL_CreateWindow("Alloy Engine", 100, 100, width_, height_, SDL_WINDOW_VULKAN);
		if (window_ == nullptr) {
			std::cerr << "SDL_CreateWindow Error : " << SDL_GetError() << "\n";
			return false;
		}

		return true;
	}

SDL_Window* Window::GetWindow() {
	return window_;
}

std::vector<const char*> Window::GetVulkanExtensions() {
	//SDL extensions
	uint32_t sdlExtensionCount = 0;
	SDL_Vulkan_GetInstanceExtensions(window_, &sdlExtensionCount, nullptr);
	std::vector<const char*> sdlExtension(sdlExtensionCount);
	SDL_Vulkan_GetInstanceExtensions(window_, &sdlExtensionCount, sdlExtension.data());

	return sdlExtension;
}
void Window::Destroy() {
	SDL_Quit();
}
} //namespace alloy::sdlwrapper

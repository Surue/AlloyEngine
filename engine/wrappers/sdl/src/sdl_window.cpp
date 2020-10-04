#include <sdl_window.h>

#include <iostream>

namespace alloy::sdlwrapper {
bool SDLWindow::Init() {
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

SDL_Window* SDLWindow::GetWindow() const {
	return window_;
}

void SDLWindow::Destroy() {
	SDL_Quit();
}
} //namespace alloy::sdlwrapper

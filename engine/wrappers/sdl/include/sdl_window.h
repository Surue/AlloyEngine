#pragma once

#include <SDL.h>
#include <SDL_vulkan.h>

namespace alloy::sdlwrapper {
class SDLWindow {
public:
	SDLWindow() = default;

	virtual ~SDLWindow() {
		SDL_DestroyWindow(window_);
	}

	SDL_Window* operator &() const {
		return window_;
	}

	bool Init();

	SDL_Window* GetWindow() const;

	void Destroy();

protected:
	SDL_Window* window_ = nullptr;

	int width_ = 720;
	int height_ = 640;
};
} //namespace alloy

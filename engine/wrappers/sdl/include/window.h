#pragma once

#include <vector>
#include <iostream>

#include <SDL.h>
#include <SDL_vulkan.h>

namespace alloy::sdlwrapper {
class Window {
public:
	Window() = default;

	~Window() {
		SDL_DestroyWindow(window_);
	}

	SDL_Window* operator &() const {
		return window_;
	}

	bool Init();

	SDL_Window* GetWindow() const;

	std::vector<const char*> GetVulkanExtensions() const;

	void Destroy();

private:
	SDL_Window* window_ = nullptr;

	int width_ = 720;
	int height_ = 640;
};
} //namespace alloy

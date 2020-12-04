#pragma once
#include <SFML/Graphics.hpp>

#include <vector.h>

namespace alloy {
namespace graphics {
struct WindowInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class Window {
public:
	Window(const WindowInitSettings& initSettings) :
		windowSize_(initSettings.windowSize),
		windowName_(initSettings.windowName) {
		
	}

	void Init() {
		window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize_.x, windowSize_.y), &windowName_[0]);
	}

	bool IsOpen() const {
		return window_->isOpen();
	}

	void Close() const {
		window_->close();
	}

	void Clear() const {
		window_->clear();
	}

	void Display() const {
		window_->display();
	}

	const sf::Window& GetSFMLWindow() const {
		return *window_;
	}

	const bool PollEvent(sf::Event& event) const {
		return window_->pollEvent(event);
	}
private:
	std::unique_ptr<sf::RenderWindow> window_;

	math::ivec2 windowSize_;
	std::string_view windowName_;
};
} //namespace graphics
} //namespace alloy

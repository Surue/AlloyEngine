#pragma once

#include <string_view>
#include <vector.h>

namespace alloy {
struct EngineInitSettings {
	std::string_view windowName;
	math::ivec2 windowSize;
};

class Engine {
public:
	Engine(const EngineInitSettings& initSettings) {
		windowSize_ = initSettings.windowSize;
		windowName_ = initSettings.windowName;
	}

	void Init() {
		window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize_.x, windowSize_.y), &windowName_[0]);
	}

	void Run() {
        while (window_->isOpen())
        {
            sf::Event event;
            while (window_->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window_->close();
            }
        
            window_->clear();
        	
            window_->display();
        }
	}

	void Destroy() {
		
	}
private:
	std::unique_ptr<sf::RenderWindow> window_;

	math::ivec2 windowSize_;
	std::string_view windowName_;
};
} //namespace alloy

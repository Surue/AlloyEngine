#include <input_manager.h>

#include <graphics_engine.h>

namespace alloy::inputs {

void InputManager::Update() {
	for (size_t i = 0; i < static_cast<int>(KeyCode::KEYBOARD_SIZE); i++) {
		if (keyStates_[i] == KeyState::UP) {
			keyStates_[i] = KeyState::NONE;
		} else if (keyStates_[i] == KeyState::DOWN) {
			keyStates_[i] = KeyState::HELD;
		}
	}

	sf::Event event;
	while (graphicsEngine_.GetWindow().PollEvent(event)) {
		if (event.type == sf::Event::Closed)
			callbackCloseWindow_();

		if (event.type == sf::Event::KeyPressed) {
			keyStates_[event.key.code] = KeyState::DOWN;
		}

		if (event.type == sf::Event::KeyReleased) {
			keyStates_[event.key.code] = KeyState::UP;
		}
	}
}
}

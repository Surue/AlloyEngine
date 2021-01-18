#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

//TODO the input manager cannot know what is the graphic engine
namespace alloy::graphics {
	class GraphicsEngine;
}

namespace alloy::inputs {
enum class KeyCode : int16_t {
	UNKNOWN = sf::Keyboard::Unknown,
	A = sf::Keyboard::A,
	B = sf::Keyboard::B,
	C = sf::Keyboard::C,
	D = sf::Keyboard::D,
	E = sf::Keyboard::E,
	F = sf::Keyboard::F,
	G = sf::Keyboard::G,
	H = sf::Keyboard::H,
	I = sf::Keyboard::I,
	J = sf::Keyboard::J,
	K = sf::Keyboard::K,
	L = sf::Keyboard::L,
	M = sf::Keyboard::M,
	N = sf::Keyboard::N,
	O = sf::Keyboard::O,
	P = sf::Keyboard::P,
	Q = sf::Keyboard::Q,
	R = sf::Keyboard::R,
	S = sf::Keyboard::S,
	T = sf::Keyboard::T,
	U = sf::Keyboard::U,
	V = sf::Keyboard::V,
	W = sf::Keyboard::W,
	X = sf::Keyboard::X,
	Y = sf::Keyboard::Y,
	Z = sf::Keyboard::Z,
	KEY_0 = sf::Keyboard::Num0,
	KEY_1 = sf::Keyboard::Num1,
	KEY_2 = sf::Keyboard::Num2,
	KEY_3 = sf::Keyboard::Num3,
	KEY_4 = sf::Keyboard::Num4,
	KEY_5 = sf::Keyboard::Num5,
	KEY_6 = sf::Keyboard::Num6,
	KEY_7 = sf::Keyboard::Num7,
	KEY_8 = sf::Keyboard::Num8,
	KEY_9 = sf::Keyboard::Num9,
	ESCAPE = sf::Keyboard::Escape,
	LEFT_CTRL = sf::Keyboard::LControl,
	LEFT_SHIT = sf::Keyboard::LShift,
	LEFT_ALT = sf::Keyboard::LAlt,
	LEFT_SYSTEM = sf::Keyboard::LSystem,
	RIGHT_CTRL = sf::Keyboard::RControl,
	RIGHT_SHIFT = sf::Keyboard::RShift,
	RIGHT_ALT = sf::Keyboard::RAlt,
	RIGHT_SYSTEM = sf::Keyboard::RSystem,
	MENU = sf::Keyboard::Menu,
	LEFT_BRACKET = sf::Keyboard::LBracket,
	RIGHT_BRACKET = sf::Keyboard::RBracket,
	SEMICOLON = sf::Keyboard::SemiColon,
	COMMA = sf::Keyboard::Comma,
	PERIOD = sf::Keyboard::Period,
	QUOTE = sf::Keyboard::Quote,
	SLASH = sf::Keyboard::Slash,
	BACKSLASH = sf::Keyboard::BackSlash,
	TILDE = sf::Keyboard::Tilde,
	EQUALS = sf::Keyboard::Equal,
	MINUS = sf::Keyboard::Dash,
	SPACE = sf::Keyboard::Space,
	RETURN = sf::Keyboard::Return,
	BACKSPACE = sf::Keyboard::BackSpace,
	TAB = sf::Keyboard::Tab,
	PAGE_UP = sf::Keyboard::PageUp,
	PAGE_DOWN = sf::Keyboard::PageDown,
	END = sf::Keyboard::End,
	HOME = sf::Keyboard::Home,
	INSERT = sf::Keyboard::Insert,
	DELETE = sf::Keyboard::Delete,
	PAD_PLUS = sf::Keyboard::Add,
	KEYPAD_MINUS = sf::Keyboard::Subtract,
	KEYPAD_MULTIPLY = sf::Keyboard::Multiply,
	KEYPAD_DIVIDE = sf::Keyboard::Divide,
	LEFT = sf::Keyboard::Left,
	RIGHT = sf::Keyboard::Right,
	UP = sf::Keyboard::Up,
	DOWN = sf::Keyboard::Down,
	KEYPAD_0 = sf::Keyboard::Numpad0,
	KEYPAD_1 = sf::Keyboard::Numpad1,
	KEYPAD_2 = sf::Keyboard::Numpad2,
	KEYPAD_3 = sf::Keyboard::Numpad3,
	KEYPAD_4 = sf::Keyboard::Numpad4,
	KEYPAD_5 = sf::Keyboard::Numpad5,
	KEYPAD_6 = sf::Keyboard::Numpad6,
	KEYPAD_7 = sf::Keyboard::Numpad7,
	KEYPAD_8 = sf::Keyboard::Numpad8,
	KEYPAD_9 = sf::Keyboard::Numpad9,
	KEY_F1 = sf::Keyboard::F1,
	KEY_F2 = sf::Keyboard::F2,
	KEY_F3 = sf::Keyboard::F3,
	KEY_F4 = sf::Keyboard::F4,
	KEY_F5 = sf::Keyboard::F5,
	KEY_F6 = sf::Keyboard::F6,
	KEY_F7 = sf::Keyboard::F7,
	KEY_F8 = sf::Keyboard::F8,
	KEY_F9 = sf::Keyboard::F9,
	KEY_F10 = sf::Keyboard::F10,
	KEY_F11 = sf::Keyboard::F11,
	KEY_F12 = sf::Keyboard::F12,
	KEY_F13 = sf::Keyboard::F13,
	KEY_F14 = sf::Keyboard::F14,
	KEY_F15 = sf::Keyboard::F15,
	KEY_PAUSE = sf::Keyboard::Pause,
	KEYBOARD_SIZE = sf::Keyboard::KeyCount
};

enum class KeyState : uint8_t
{
	NONE = 0,
	DOWN,
	HELD,
	UP,
};

class InputManager {
public:

	InputManager(graphics::GraphicsEngine& graphicsEngine) :
		graphicsEngine_(graphicsEngine){
		
	}

	void Init() {
	}

	void SetCallbackCloseWindow(const std::function<void()>& callback) {
		callbackCloseWindow_ = callback;
	}

	void Update();

	bool IsKeyDown(KeyCode keyCode) const {
		return keyStates_[static_cast<int>(keyCode)] == KeyState::DOWN;
	}

	bool IsKeyUp(KeyCode keyCode) const {
		return keyStates_[static_cast<int>(keyCode)] == KeyState::UP;
	}

	bool IsKeyHeld(KeyCode keyCode) const {
		return keyStates_[static_cast<int>(keyCode)] == KeyState::HELD;
	}
private:
	const graphics::GraphicsEngine& graphicsEngine_;

	std::function<void()> callbackCloseWindow_;

	std::vector<KeyState> keyStates_ = std::vector<KeyState>(static_cast<int>(KeyCode::KEYBOARD_SIZE));
};
}

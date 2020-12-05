#pragma once

#include <SFML/Graphics.hpp>

#include <log.h>

namespace alloy {
namespace graphics {
class Texture {
public:
	Texture() {
		
	}

	/// <summary>
	/// Load the texture with the given filepath
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns>True if the loading was succesfull</returns>
	bool Load(const std::string_view filePath) {
		if(!texture_.loadFromFile(&filePath[0])) {
			debug::LogError("Loading image from " + std::string(filePath) + " failed", debug::LogType::GRAPHICS); 
			return false;
		}

		return true;
	}

	const sf::Texture& GetSfTexture() const {
		return texture_;
	}
private:
	sf::Texture texture_;
};
} //namespace graphics
} //namespace alloy

#pragma once

#include <SFML/Graphics.hpp>

#include <log.h>
#include <vector.h>

namespace alloy {
namespace graphics {
/// <summary>
/// Define the texture mode:
/// - SINGLE => One image on the texture
/// - TILESET => Multiple image on the texture
/// </summary>
enum class TextureMode : uint8_t {
	SINGLE = 0,
	TILESET,
};

class Texture {
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mode">By default is set to single</param>
	/// <param name="tilesNb"></param>
	Texture(const TextureMode mode = TextureMode::SINGLE, const math::uivec2 tilesNb = math::uivec2::one) :
		mode_(mode),
		tileNb_(tilesNb){ }

	/// <summary>
	/// Load the texture with the given filepath
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns>True if the loading was succesfull</returns>
	bool Load(const std::string_view filePath) {
		if (!texture_.loadFromFile(&filePath[0])) {
			debug::LogError("Loading image from " + std::string(filePath) + " failed", debug::LogType::GRAPHICS);
			return false;
		}
		
		return true;
	}

	const sf::Texture& GetSfTexture() const {
		return texture_;
	}

	TextureMode GetTextureMode() const {
		return mode_;
	}

	/// <summary>
	/// Return the size of a tile in the texture. If the mode is set to single, return the size of the whole texture
	/// </summary>
	/// <returns></returns>
	math::uivec2 GetTileSize() const {
		if(mode_ == TextureMode::SINGLE) {
			const auto size = texture_.getSize();
			return {size.x, size.y};
		}else {
			const auto totalSize = texture_.getSize();
			return { totalSize.x / tileNb_.x, totalSize.y / tileNb_.y };
		}
	}

	/// <summary>
	/// Return the size of the texture
	/// </summary>
	/// <returns></returns>
	math::uivec2 GetTextureSize() const {
		const auto size = texture_.getSize();
		return { size.x, size.y };
	}

private:
	sf::Texture texture_;

	TextureMode mode_;

	math::uivec2 tileNb_;
};
} //namespace graphics
} //namespace alloy

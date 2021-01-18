#pragma once

#include <SFML/Graphics.hpp>

#include <vector.h>

namespace alloy {
namespace graphics {

struct TextureCoordsInPixel {

	union {
		struct {
			math::ivec2 topLeft;
			math::ivec2 topRight;
			math::ivec2 bottomRight;
			math::ivec2 bottomLeft;

		};

		math::ivec2 coord[4];
	};

	TextureCoordsInPixel() :
		topLeft(math::ivec2::zero),
		topRight(math::ivec2::zero), 
		bottomRight(math::ivec2::zero),
		bottomLeft(math::ivec2::zero) {
	}

	math::ivec2 operator[](const unsigned int index) const {
		return coord[index];
	}
};

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
	bool Load(const std::string_view filePath);

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
		} else {
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

	TextureCoordsInPixel GetTextureCoordInPixel(const int textureIndex) const {
		const auto totalSize = texture_.getSize();
		const math::uivec2 size = math::uivec2(totalSize.x, totalSize.y) / tileNb_;

		const auto coordTile = TextureIndexToTileCoords(textureIndex);

		TextureCoordsInPixel coord;
		coord.topLeft = math::ivec2( coordTile.x * size.x,coordTile.y * size.y);
		coord.topRight = math::ivec2((coordTile.x + 1) * size.x,coordTile.y * size.y);
		coord.bottomRight = math::ivec2((coordTile.x + 1) * size.x,(coordTile.y + 1) * size.y);
		coord.bottomLeft = math::ivec2(coordTile.x * size.x,(coordTile.y + 1) * size.y);

		return coord;
	}

	math::uivec2 TextureIndexToTileCoords(const int index) const {
		return { index % tileNb_.x, index / tileNb_.x };
	}

private:
	sf::Texture texture_;

	TextureMode mode_;

	math::uivec2 tileNb_;
};
} //namespace graphics
} //namespace alloy

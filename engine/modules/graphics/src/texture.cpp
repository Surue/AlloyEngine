#include <texture.h>

#include <log.h>

namespace alloy::graphics {

bool Texture::Load(const std::string_view filePath) {
	if (!texture_.loadFromFile(&filePath[0])) {
		debug::LogError("Loading image from " + std::string(filePath) + " failed", debug::LogType::GRAPHICS);
		return false;
	}

	return true;
}

math::uivec2 Texture::GetTileSize() const {
	if (mode_ == TextureMode::SINGLE) {
		const auto size = texture_.getSize();
		return {size.x, size.y};
	} else {
		const auto totalSize = texture_.getSize();
		return {totalSize.x / tileNb_.x, totalSize.y / tileNb_.y};
	}
}

math::uivec2 Texture::GetTextureSize() const {
	const auto size = texture_.getSize();
	return {size.x, size.y};
}

TextureCoordsInPixel Texture::GetTextureCoordInPixel(const int textureIndex) const {
	const auto totalSize = texture_.getSize();
	const math::uivec2 size = math::uivec2(totalSize.x, totalSize.y) / tileNb_;

	const auto coordTile = TextureIndexToTileCoords(textureIndex);

	TextureCoordsInPixel coord;
	coord.topLeft = math::ivec2(coordTile.x * size.x, coordTile.y * size.y);
	coord.topRight = math::ivec2((coordTile.x + 1) * size.x, coordTile.y * size.y);
	coord.bottomRight = math::ivec2((coordTile.x + 1) * size.x, (coordTile.y + 1) * size.y);
	coord.bottomLeft = math::ivec2(coordTile.x * size.x, (coordTile.y + 1) * size.y);

	return coord;
}
}

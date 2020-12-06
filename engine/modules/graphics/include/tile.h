#pragma once

#include <texture.h>

namespace alloy {
namespace graphics {
class Tile {
public:
	Tile(const Texture& tileset, const int textureIndex) :
		tileset_(tileset),
		textureIndex_(textureIndex),
		textureCoords_(tileset.GetTextureCoordInPixel(textureIndex)){
	}

	void SetSprite(const int newTextureIndex) {
		textureIndex_ = newTextureIndex;
		textureCoords_ = tileset_.GetTextureCoordInPixel(textureIndex_);
	}

	const TextureCoordsInPixel& GetTextureCoordsInPixel() const {
		return textureCoords_;
	}
private:
	const Texture& tileset_;
	int textureIndex_;

	TextureCoordsInPixel textureCoords_;
};
} //namespace graphics
} //namespace alloy

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
}

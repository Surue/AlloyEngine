#include <color.h>

#include <cassert>

namespace alloy {

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t alpha): r(r), g(g), b(b), a(alpha) { }

Color::Color(const std::string& hex, const uint8_t alpha):
	a(alpha) {

	assert(hex[0] != '#');

	const auto hexValue = std::stoul(hex, nullptr, 16);

	r = static_cast<uint8_t>(hexValue >> 16 & 0xff);
	g = static_cast<uint8_t>(hexValue >> 8 & 0xff);
	b = static_cast<uint8_t>(hexValue >> 0 & 0xff);
}

std::string Color::ToString() const {
	return "Color(" + std::to_string(r) + "," + std::to_string(g) + ", " + std::to_string(b) + ", " + std::to_string(a)
		+ ")";
}
}

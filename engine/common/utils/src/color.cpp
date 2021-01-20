#include <color.h>

namespace alloy {

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t alpha): r(r), g(g), b(b), a(alpha) { }

Color::Color(const std::string& hex, const uint8_t alpha):
	a(alpha) {

	assert(hex[0] != '#');

	const auto hexValue = std::stoul(hex, nullptr, 16);

	r = static_cast<float>((hexValue >> 16) & 0xff) / 255.0f;
	g = static_cast<float>((hexValue >> 8) & 0xff) / 255.0f;
	b = static_cast<float>((hexValue >> 0) & 0xff) / 255.0f;
}
}

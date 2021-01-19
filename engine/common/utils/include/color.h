#pragma once
#include <cassert>
#include <cstdint>
#include <string>

namespace alloy {
struct Color {
public:
	union {
		struct {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};

		uint8_t coord[4];
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="alpha"></param>
	Color(const uint8_t r = 0, const uint8_t g = 0, const uint8_t b = 0, const uint8_t alpha = 255) : r(r), g(g), b(b), a(alpha) {
		
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hex">Do not add # at the start</param>
	/// <param name="alpha"></param>
	Color(const std::string& hex, const uint8_t alpha = 255) :
		a(alpha)
	{
		
		assert(hex[0] != '#');

		const auto hexValue = std::stoul(hex, nullptr, 16);

		r = static_cast<float>((hexValue >> 16) & 0xff) / 255.0f;
		g = static_cast<float>((hexValue >> 8) & 0xff) / 255.0f;
		b = static_cast<float>((hexValue >> 0) & 0xff) / 255.0f;
	}

	static const Color clear;
	static const Color black;
	static const Color grey;
	static const Color silver;
	static const Color white;
	static const Color maroon;
	static const Color red;
	static const Color olive;
	static const Color yellow;
	static const Color orange;
	static const Color green;
	static const Color lime;
	static const Color teal;
	static const Color aqua;
	static const Color navy;
	static const Color blue;
	static const Color purple;
	static const Color fuchsia;
private:
};

inline const Color Color::clear("#000000", 0.0f);
inline const Color Color::black("#000000");
inline const Color Color::grey("#808080");
inline const Color Color::silver("#C0C0C0");
inline const Color Color::white("#FFFFFF");
inline const Color Color::maroon("#800000");
inline const Color Color::red("#FF0000");
inline const Color Color::olive("#808000");
inline const Color Color::yellow("#FFFF00");
inline const Color Color::orange("#FF8800");
inline const Color Color::green("#00FF00");
inline const Color Color::lime("#008000");
inline const Color Color::teal("#008080");
inline const Color Color::aqua("#00FFFF");
inline const Color Color::navy("#000080");
inline const Color Color::blue("#0000FF");
inline const Color Color::purple("#800080");
inline const Color Color::fuchsia("#FF00FF");
}

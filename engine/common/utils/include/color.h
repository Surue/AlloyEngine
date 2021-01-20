#pragma once

#include <cstdint>
#include <string>
#include <istream>

namespace alloy {
struct Color {
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
	Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t alpha = 255);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="hex">Do not add # at the start</param>
	/// <param name="alpha"></param>
	Color(const std::string& hex, uint8_t alpha = 255);

	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& os, const Color& color) {
		os << "Color(" << color.r << "," << color.g << ", " << color.b << ", " << color.a << ")";
		return os;
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
};

inline const Color Color::clear("000000", 0.0f);
inline const Color Color::black("000000");
inline const Color Color::grey("808080");
inline const Color Color::silver("C0C0C0");
inline const Color Color::white("FFFFFF");
inline const Color Color::maroon("800000");
inline const Color Color::red("FF0000");
inline const Color Color::olive("808000");
inline const Color Color::yellow("FFFF00");
inline const Color Color::orange("FF8800");
inline const Color Color::green("00FF00");
inline const Color Color::lime("008000");
inline const Color Color::teal("008080");
inline const Color Color::aqua("00FFFF");
inline const Color Color::navy("000080");
inline const Color Color::blue("0000FF");
inline const Color Color::purple("800080");
inline const Color Color::fuchsia("FF00FF");
}

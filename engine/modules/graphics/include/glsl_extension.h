#pragma once

#include <SFML/Graphics/Glsl.hpp>

#include <vector.h>

#include <color.h>

namespace alloy::graphics {
template<typename T>
static sf::Glsl::Vec2 Vec2ToGlslVec2(const sf::Vector2<T> vec) {
	return sf::Glsl::Vec2(vec.x, vec.y);
}

static sf::Glsl::Vec2 Vec2ToGlslVec2(const math::fvec2 vec) {
	return sf::Glsl::Vec2(vec.x, vec.y);
}

static sf::Glsl::Vec3 Vec3ToGlslVec3(const math::fvec3& vec) {
	return sf::Glsl::Vec3(vec.x, vec.y, vec.z);
}

static sf::Glsl::Vec4 ColorToGlslVec4(const Color& color) {
	return sf::Glsl::Vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}
}

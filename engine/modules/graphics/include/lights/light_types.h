#pragma once

#include <color.h>
#include <vector.h>

#include <interfaces/interface_drawable.h>

#include <sfml_graphics_extension.h>

namespace alloy::graphics {
enum class LightType : uint8_t {
	AMBIENT,
	POINT
};
//TODO If possible avoid inheritance
struct Light : IDrawable {
	virtual ~Light() = default;
	virtual LightType GetLightType() = 0;
};

struct AmbientLight : Light {
	AmbientLight(const Color& color = Color::white) : color(color) {}
	
	Color color;

	LightType GetLightType() override {
		return LightType::AMBIENT;
	}

	void Draw(sf::RenderTarget& renderTarget) override {
		renderTarget.clear(ColorToSfColor(color));
	}
};

struct PointLight : Light {
	Color color;
	math::fvec2 position;
	float radius = 1;

	PointLight(const Color& color = Color::white, const math::fvec2 position = math::fvec2::zero, const float radius = 1) :
		color(color),
		position(position),
		radius(radius){
		
	}

	LightType GetLightType() override {
		return LightType::POINT;
	}

	void Draw(sf::RenderTarget& renderTarget) override {
		sf::CircleShape circleShape;
		circleShape.setRadius(radius);
		circleShape.setFillColor(ColorToSfColor(color));
		circleShape.setPosition(position.x, position.y);

		renderTarget.draw(circleShape, sf::BlendAdd);
	}
};
}

#pragma once

#include <color.h>
#include <vector.h>

#include <interfaces/interface_drawable.h>

#include <sfml_graphics_extension.h>

#include <iostream>

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

	void Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) override {
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

	void Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) override {
		sf::CircleShape circleShape;
		circleShape.setRadius(radius);
		circleShape.setFillColor(ColorToSfColor(color));
		circleShape.setPosition(position.x, position.y);

		//shader.setUniform("lightPos", sf::Glsl::Vec2(position.x, position.y));
		//shader.setUniform("lightColor", sf::Glsl::Vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));

		sf::RenderStates renderState;
		renderState.blendMode = sf::BlendAdd;
		renderState.shader = &shader;

		renderTarget.draw(circleShape, renderState);
	}
};
}

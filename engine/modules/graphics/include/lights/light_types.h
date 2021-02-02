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

	void Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) override {
		renderTarget.clear(ColorToSfColor(color));
	}
};

struct PointLight : Light {
	Color color;
	math::fvec2 position;
	float radius = 1.0f;
	float intensity = 1.0f;

	PointLight(const Color& color = Color::white, const math::fvec2 position = math::fvec2::zero,
	           const float radius = 1.0f, const float intensity = 1.0f);

	LightType GetLightType() override {
		return LightType::POINT;
	}

	//TODO Remove out parameters => Create class for shader + draw from outside lights
	void Draw(sf::RenderTarget& renderTarget, sf::Shader& shader) override;

private:
	const math::fvec3 falloff_ = math::fvec3(0.1f, 3.0f, 100.0f);
};
}

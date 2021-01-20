#pragma once

#include <color.h>
#include <vector.h>

namespace alloy::graphics {
enum class LightType : uint8_t {
	AMBIENT,
	POINT
};
//TODO If possible avoid inheritance
struct Light {
	virtual ~Light() {}
	virtual LightType GetLightType() = 0;
};

struct AmbientLight : Light {
	Color color;
	
	LightType GetLightType() override {
		return LightType::AMBIENT;
	}
};

struct PointLight : Light {
	Color color;
	math::fvec2 position;
	float radius = 1;

	LightType GetLightType() override {
		return LightType::POINT;
	}
};
}
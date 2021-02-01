#pragma once
#include <SFML/Graphics.hpp>

#include <service_locator.h>
#include <lights/light_types.h>

namespace alloy::graphics {
class LightManagerBase {
public:
	virtual void Init() = 0;

	virtual void Draw(sf::RenderTarget& target) = 0;
};

class LightManagerNull : public LightManagerBase {
public:
	void Init() override {}

	void Draw(sf::RenderTarget& target) override {}
};

class LightManager : public LightManagerBase {
public:
	LightManager() { 
		lightMap_.create(600, 600); //TODO Remove magic number
		const std::string fragmentShader = 
		" \
		vec4 lightColor = vec4(1, 1, 1, 1); \
		vec3 falloff = vec3(0.1, 3, 100);\
		float intensity = 1.0;\
		float radius = 300;\
		vec2 iResolution = vec2(600, 600);\
		vec3 pos = vec3(300, 300, 0);\
		\
		void main() \
		{ \
			vec2 uv = gl_FragCoord.xy / iResolution.xy;\
\
			pos.xy = pos.xy / iResolution.xy;\
\
			float dist = distance(uv, pos.xy);\
\
			vec3 d = lightColor.rgb * lightColor.a;\
\
			float attenuation = intensity / (falloff.x + (falloff.y * dist) + (falloff.z * dist * dist));\
\
			vec3 light = d * attenuation;\
\
			light = pow(light, vec3(1.0 / 2.2));\
\
			vec4 result = vec4(light, attenuation);\
\
			gl_FragColor = result;\
		}";
		
		lightShader_.loadFromMemory(fragmentShader, sf::Shader::Fragment);
	}

	void Init() override {
		
	}

	void Draw(sf::RenderTarget& target) override;
private:
	sf::RenderTexture lightMap_;

	AmbientLight ambientLight_{Color::black};

	sf::Shader lightShader_;
};

using ServiceLightManager = ServiceLocator<LightManagerBase, LightManagerNull>;
}

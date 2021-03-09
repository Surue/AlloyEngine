#pragma once

#include <engine.h>

namespace alloy {
struct ApplicationInitSettings {
	std::string application_name;
	math::ivec2 window_size;
};

class Application {
public:
	explicit Application(const ApplicationInitSettings& applicationInitSettings) : engine_({applicationInitSettings.application_name, applicationInitSettings.window_size}) {}

	virtual ~Application() {
		engine_.Destroy();
	}

	void Start() {
		Init();
		
		engine_.Init();

		engine_.Run();
	}

protected:
	virtual void Init() = 0;

	void AddSystem(ecs::System& system) {
		engine_.AddSystem(system);
	}

private:
	
	Engine engine_;
};
}

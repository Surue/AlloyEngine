#pragma once

#include <engine.h>

namespace alloy {
struct ApplicationInitSettings {
	std::string application_name;
	math::ivec2 window_size;
};

class Application {
public:
	Application(const ApplicationInitSettings& applicationInitSettings) : engine_({applicationInitSettings.application_name, applicationInitSettings.window_size}) {}

	virtual ~Application() {
		engine_.Destroy();
	}

	void Start() {
		engine_.Init();

		Init();

		engine_.Run();
	}

protected:
	virtual void Init() = 0;
	
	void AddCallbackUpdate(const std::function<void()> callback) {
		engine_.AddCallbackUpdate(callback);
	}

private:
	
	Engine engine_;
};
}
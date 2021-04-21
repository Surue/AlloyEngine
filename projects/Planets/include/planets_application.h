#pragma once

#include <application.h>

class PlanetsApplication : public alloy::Application {
public:
	PlanetsApplication(const alloy::ApplicationInitSettings& applicationInitSettings);

protected:
    void Init() override {}
};

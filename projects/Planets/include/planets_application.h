#pragma once

#include <application.h>
#include <planets_system.h>

class PlanetsApplication : public alloy::Application {
public:
	PlanetsApplication(const alloy::ApplicationInitSettings& applicationInitSettings);

protected:
    void Init() override {}

private:
	PlanetsSystem planetsSystem_;
};

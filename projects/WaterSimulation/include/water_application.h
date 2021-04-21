#pragma once

#include <application.h>
#include <water_simulation_system.h>

class WaterApplication : public alloy::Application {
public:
	WaterApplication(const alloy::ApplicationInitSettings& applicationInitSettings);

protected:
    void Init() override {}

private:
    WaterSimulationSystem cellularAutomataSystem_;
};

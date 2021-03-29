#pragma once

#include <application.h>

#include <water_simulation_system.h>

class EmptyApp : public alloy::Application {
public:
    EmptyApp(const alloy::ApplicationInitSettings& applicationInitSettings) : Application(applicationInitSettings) {
        RegisterSystem(cellularAutomataSystem_);
    }

protected:
    void Init() override {}

private:
    WaterSimulationSystem cellularAutomataSystem_;
};

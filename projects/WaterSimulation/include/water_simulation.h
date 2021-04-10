#pragma once

#include <application.h>

#include <water_simulation_system.h>

class WaterApplication : public alloy::Application {
public:
    WaterApplication(const alloy::ApplicationInitSettings& applicationInitSettings) :
		Application(applicationInitSettings),
		cellularAutomataSystem_(engine_.GetGraphicsEngineRef().GetTilemapManagerRef()){
        RegisterSystem(cellularAutomataSystem_);
    }

protected:
    void Init() override {}

private:
    WaterSimulationSystem cellularAutomataSystem_;
};

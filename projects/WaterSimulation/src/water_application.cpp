#include <water_application.h>

WaterApplication::WaterApplication(const alloy::ApplicationInitSettings& applicationInitSettings):
	Application(applicationInitSettings),
	cellularAutomataSystem_(engine_.GetGraphicsEngineRef().GetTilemapManagerRef()) {
	RegisterSystem(cellularAutomataSystem_);
}

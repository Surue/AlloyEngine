#include <planets_application.h>

PlanetsApplication::PlanetsApplication(const alloy::ApplicationInitSettings& applicationInitSettings):
	Application(applicationInitSettings),
	planetsSystem_() {
	RegisterSystem(planetsSystem_);
}

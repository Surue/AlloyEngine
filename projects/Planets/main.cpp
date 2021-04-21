#include <array>

#include <lib/Remotery.h>

#include <planets_application.h>

int main() {
    Remotery* rmt;
    rmt_CreateGlobalInstance(&rmt);
    const alloy::ApplicationInitSettings engineInitSettings{
        "Planets",
        math::ivec2(600, 600)
    };

    PlanetsApplication app(engineInitSettings);

    app.Start();

    rmt_DestroyGlobalInstance(rmt);
    return EXIT_SUCCESS;
}

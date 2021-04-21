#include <array>

#include <lib/Remotery.h>

#include <water_application.h>

int main() {
    Remotery* rmt;
    rmt_CreateGlobalInstance(&rmt);
    const alloy::ApplicationInitSettings engineInitSettings{
        "Water Simulation",
        math::ivec2(600, 600)
    };

    WaterApplication app(engineInitSettings);

    app.Start();

    rmt_DestroyGlobalInstance(rmt);
    return EXIT_SUCCESS;
}

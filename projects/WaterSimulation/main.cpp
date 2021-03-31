#include <array>

#include <lib/Remotery.h>

#include <water_simulation.h>

int main() {
    Remotery* rmt;
    rmt_CreateGlobalInstance(&rmt);
    alloy::ApplicationInitSettings engineInitSettings{
        "Water Simulation",
        math::ivec2(600, 600)
    };

    WaterApplication cellularAutomata(engineInitSettings);

    cellularAutomata.Start();

    rmt_DestroyGlobalInstance(rmt);
    return EXIT_SUCCESS;
}


#include <SFML/Graphics.hpp>
#include <vector.h>

#include <engine.h>

int main() {

    alloy::EngineInitSettings engineInitSettings{
        "AlloyEngine",
        alloy::math::ivec2(600, 600)
    };
	
    alloy::Engine engine(engineInitSettings);

    engine.Init();

    engine.Run();

    return EXIT_SUCCESS;
}


#include <vector.h>

#include <engine.h>

class CellularAutomataSystem {
public:
    void Init() {
        tiles_.resize(tilemapSize_.x * tilemapSize_.y);
    }
	
    void OnUpdate() {
        alloy::debug::Log("Update");
    }

private:
    std::vector<int> tiles_;

    alloy::math::ivec2 tilemapSize_;
};

class CellularAutomata {
public:
	CellularAutomata(const alloy::EngineInitSettings& engineInitSettings) :
        engine_(engineInitSettings){
	}

    void Init() {
        engine_.Init();

        engine_.AddCallbackUpdate([this]() {cellularAutomataSystem_.OnUpdate(); });
	}

	void Run() {
        engine_.Run();
	}
private:
    alloy::Engine engine_;
    CellularAutomataSystem cellularAutomataSystem_;
};

int main() {

    alloy::EngineInitSettings engineInitSettings{
        "CellularA Automata",
        alloy::math::ivec2(600, 600)
    };
	
    CellularAutomata cellularAutomata(engineInitSettings);

    cellularAutomata.Init();

    cellularAutomata.Run();

    return EXIT_SUCCESS;
}

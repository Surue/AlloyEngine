#pragma once

#include <array>
#include <random>

#include <systems/system.h>
#include <vector.h>
#include <tilemap_manager.h>

class WaterSimulationSystem : public alloy::ecs::System {
public:
    WaterSimulationSystem(alloy::graphics::TilemapManager& tilemapManager) :
        System({ alloy::ecs::SystemExecutionFlags::INIT, alloy::ecs::SystemExecutionFlags::UPDATE }),
        tilemapManager_(tilemapManager) {}

    void OnInit() override;

    void OnUpdate() override;

private:
    math::ivec2 IndexToCoords(int index) const;

    int CoordsToIndex(math::ivec2 coords) const;

    float CalculateVerticalFlowValue(float remainingLiquid, int indexDest);

    void UpdateWater();

    void CellularStep();

    std::vector<int> tiles_;

    std::vector<float> waterPressure_;

    math::ivec2 tilemapSize_{ 100, 100 };

    enum class TileState : uint8_t {
        SOLID = 0,
        LIQUID,
        AIR
    };

    std::vector<TileState> tileStates_;

    std::array<math::ivec2, 8> neighborOffset_{ {
        {-1, -1},
        {0, -1},
        { 1, -1 },
        { -1, 0 },
        { 1, 0 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 }
    } };

    //Tiles indexs
    const int solidTile_ = 10;
    const int freeTile_ = 13;

    const int waterTile1_ = 0;
    const int waterTile2_ = 1;
    const int waterTile3_ = 2;
    const int waterTile4_ = 3;
    const int waterTile5_ = 4;

    const int timeBetweenUpdateInMS_ = 50;
    const float maxPressure_ = 1.0f;
    const float maxCompression_ = 0.25f;
    const float minFlow_ = 1.0f;
    const float maxFlow_ = 4.0f;
    const float flowSpeed_ = 1.0f;
    const float minPressure_ = 0.005f;
    const int invalidWaterPressure_ = -1;
    int timeBetweenUpdate_ = 0;

    const math::uivec2 topLeft_{ 0, 0 };
    const math::uivec2 bottomRight_{ 100, 100 };

    std::vector<alloy::graphics::Tile> tilesToUpdate;
    alloy::graphics::TilemapManager& tilemapManager_;
};

#include <vector>
#include <flecs.h>
#include "LevelBuilder.hpp"
#include "flecs_ids.hpp"


LevelBuilder::LevelBuilder() {}
LevelBuilder::~LevelBuilder() {}

void LevelBuilder::buildEasyLevel(flecs::world &world) {
    const unsigned int mapDimensions = 16;

    for (int y = 0; y < mapDimensions; y++) {
        for (int x = 0; x < mapDimensions; x++) {
            world.entity().
                set<Position>({(double) x, (double) y});
        };
    };
}
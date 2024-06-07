#include <flecs.h>
#include <flecs_ids.hpp>
#include "GameModel.hpp"
#include "LevelBuilder.hpp"


GameModel::GameModel(int difficulty) {
    LevelBuilder levelBuilder;
    switch (difficulty) {
        case 0: levelBuilder.buildEasyLevel(this->world); break;
        case 1: levelBuilder.buildMediumLevel(this->world); break;
        case 2: levelBuilder.buildHardLevel(this->world); break;
    }

    flecs::entity start = this->world.lookup("Start");
    const Position* startPosition = start.get<Position>();

    this->world.entity("Cursor")
        .set<Position>({startPosition->x, startPosition->y})
        .set<Tick>({0, 8});
}
GameModel::~GameModel() {
    this->world.each([](flecs::entity entity) {
        entity.destruct();
    });
}
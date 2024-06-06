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

    const Position* startPosition = this->world.lookup("Start").get<Position>();

    this->world.entity("Cursor")
        .set<Position>(*startPosition)
        .set<Tick>({0, 6});
    
}
GameModel::~GameModel() {
    this->world.each([](flecs::entity entity) {
        entity.destruct();
    });
}
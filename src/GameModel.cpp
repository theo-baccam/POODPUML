#include <flecs.h>
#include <flecs_ids.hpp>
#include "GameModel.hpp"
#include "LevelBuilder.hpp"


GameModel::GameModel(int difficulty) {
    LevelBuilder levelBuilder;
    this->world.entity("Cursor")
        .set<Position>({0, 0})
        .set<Tick>({0, 6});
    
    switch (difficulty) {
        case 0: levelBuilder.buildEasyLevel(this->world); break;
        case 1: levelBuilder.buildMediumLevel(this->world); break;
        case 2: levelBuilder.buildHardLevel(this->world); break;
    }
}
GameModel::~GameModel() {
    this->world.each([](flecs::entity entity) {
        entity.destruct();
    });
}
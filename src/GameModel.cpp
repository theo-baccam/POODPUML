#include <flecs.h>
#include "GameModel.hpp"
#include "LevelBuilder.hpp"


GameModel::GameModel(int difficulty) {
    LevelBuilder levelBuilder;
    switch (difficulty) {
        case 0: levelBuilder.buildEasyLevel(this->world); break;
        case 1: break;
        case 2: break;
    }
}
GameModel::~GameModel() {
    this->world.each([](flecs::entity entity) {
        entity.destruct();
    });
}
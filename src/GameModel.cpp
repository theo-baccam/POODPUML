#include <flecs.h>
#include "GameModel.hpp"
#include "LevelBuilder.hpp"


GameModel::GameModel(int difficulty) {
    LevelBuilder levelBuilder;
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
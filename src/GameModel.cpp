#include <flecs.h>
#include "GameModel.hpp"


GameModel::GameModel(int difficulty) {
    switch (difficulty) {
        case 0: break;
        case 1: break;
        case 2: break;
    }
}
GameModel::~GameModel() {
    this->world.each([](flecs::entity entity) {
        entity.destruct();
    });
}
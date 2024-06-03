#pragma once
#include <flecs.h>


class GameModel {
    public:
        GameModel(int difficulty);
        ~GameModel();

        flecs::world world;
};
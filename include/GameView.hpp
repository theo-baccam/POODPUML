#pragma once
#include <flecs.h>
#include "flecs_ids.hpp"


class GameView {
    public:
        GameView();
        ~GameView();

        void drawFloor(flecs::query<FloorTag, Position> &floorQuery);
};
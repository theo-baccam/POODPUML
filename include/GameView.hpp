#pragma once
#include <raylib.h>
#include <flecs.h>
#include "flecs_ids.hpp"
#include "AssetsLoader.hpp"


class GameView {
    private:
        AssetsLoader assetsLoader;

    public:
        GameView(int x, int y);
        ~GameView();

        Camera2D camera;

        Vector2 transformGridOblique(double x, double y);
        void drawFloor(flecs::query<FloorTag, Position> &floorQuery);
};
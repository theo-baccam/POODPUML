#include <flecs.h>
#include <raylib.h>
#include "GameView.hpp"
#include "flecs_ids.hpp"
#include "colors.hpp"


GameView::GameView() {}
GameView::~GameView() {}

void GameView::drawFloor(flecs::query<FloorTag, Position> &floorQuery) {
    floorQuery.each([](FloorTag floorTag, Position position) {
        DrawPixel(position.x, position.y, COLOR5);
    });
};
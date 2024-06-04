#include <flecs.h>
#include <raylib.h>
#include "GameView.hpp"
#include "flecs_ids.hpp"
#include <AssetsLoader.hpp>
#include "colors.hpp"
#define SPRITE_DIMENSIONS 32


GameView::GameView() {
    this->camera.target = (Vector2) {0, 0};
    this->camera.offset = (Vector2) {
        (float) GetScreenWidth() / 2,
        (float) GetScreenHeight() / 2
    };
    this->camera.zoom = 2.0;
    this->camera.rotation = 0;
}
GameView::~GameView() {}

Vector2 GameView::transformGridOblique(double x, double y) {
    Vector2 isometricCoordinates = {
        (float) (x * (SPRITE_DIMENSIONS / 2)
        - (y * (SPRITE_DIMENSIONS / 2))),
        (float) y * (SPRITE_DIMENSIONS / 2)
    };
    
    return isometricCoordinates;
};

void GameView::drawFloor(flecs::query<FloorTag, Position> &floorQuery) {
    floorQuery.each([&](FloorTag floorTag, Position position) {
        DrawTextureV(
            this->assetsLoader.floorTileTexture,
            this->transformGridOblique(position.x, position.y),
            WHITE
        );
    });
};
#include <raylib.h>
#include <flecs.h>
#include "flecs_ids.hpp"
#include "GameController.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
#include "colors.hpp"

#include <iostream>

GameController::GameController():
    model(2),
    view(
        this->model.world.lookup("Cursor").get<Position>()->x,
        this->model.world.lookup("Cursor").get<Position>()->y
    ) {
    this->floorQuery = this->model.world.query<FloorTag, Position>();
    this->creatingPath = true;
}
GameController::~GameController() {}

void GameController::run() {
    flecs::entity cursor = this->model.world.lookup("Cursor");

    int cursorTick = cursor.get<Tick>()->tick;
    int cursorMaxTick = cursor.get<Tick>()->maxTick;

    double cursorX = cursor.get<Position>()->x;
    double cursorY = cursor.get<Position>()->y;

    if (
        IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) ||
        IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)
    ) {
        if (IsKeyDown(KEY_UP)) {
            flecs::entity northNeighbor = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return position.x == cursorX && position.y == cursorY - 1;
            });
            if (cursorTick == 0 && northNeighbor) cursorY -= 1;

        } else if (IsKeyDown(KEY_DOWN)) {
            flecs::entity southNeighbor = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return position.x == cursorX && position.y == cursorY + 1;
            });
            if (cursorTick == 0 && southNeighbor) cursorY += 1;

        } else if (IsKeyDown(KEY_LEFT)) {
            flecs::entity westNeighbor = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return position.x == cursorX - 1 && position.y == cursorY;
            });
            if (cursorTick == 0 && westNeighbor) cursorX -= 1;

        } else if (IsKeyDown(KEY_RIGHT)) {
            flecs::entity eastNeighbor = this->floorQuery.find([&](
                FloorTag floorTag, Position position
            ) {
                return position.x == cursorX + 1 && position.y == cursorY;
            });
            if (cursorTick == 0 && eastNeighbor) cursorX += 1;

        };
        cursor.set<Tick>({
            (cursorTick + 1 + cursorMaxTick) % cursorMaxTick, cursorMaxTick
        });
        cursor.set<Position>({cursorX, cursorY});
        this->view.camera.target = this->view.transformGridOblique(
            cursorX,
            cursorY
        );
    };
    if (
        !IsKeyDown(KEY_UP) &&
        !IsKeyDown(KEY_DOWN) &&
        !IsKeyDown(KEY_LEFT) &&
        !IsKeyDown(KEY_RIGHT)
    ) {
        cursor.set<Tick>({0, cursorMaxTick});
    };

    flecs::entity currentTile = this->floorQuery.find([&](
        FloorTag floorTag, Position position
    ) {
        return position.x == cursorX && position.y == cursorY;
    });
    if (currentTile && creatingPath && !currentTile.has<PathTag>()) {
        currentTile.add<PathTag>();
    };

    BeginDrawing();
    ClearBackground(COLOR0);

    BeginMode2D(this->view.camera);
    this->view.drawFloor(this->floorQuery);
    this->view.drawPathWithFilter(this->model.world);
    this->view.drawStartEnd(this->model.world);
    this->view.drawCursor(this->model.world.lookup("Cursor"));
    EndMode2D();

    EndDrawing();
}
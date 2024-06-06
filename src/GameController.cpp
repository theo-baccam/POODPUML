#include <raylib.h>
#include <flecs.h>
#include "flecs_ids.hpp"
#include "GameController.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
#include "colors.hpp"

GameController::GameController():
    model(2),
    view(
        this->model.world.lookup("Cursor").get<Position>()->x,
        this->model.world.lookup("Cursor").get<Position>()->y
    ) {
    this->floorQuery = this->model.world.query<FloorTag, Position>();
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
            if (cursorTick == 0) cursorY -= 1;
        } else if (IsKeyDown(KEY_DOWN)) {
            if (cursorTick == 0) cursorY += 1;
        } else if (IsKeyDown(KEY_LEFT)) {
            if (cursorTick == 0) cursorX -= 1;
        } else if (IsKeyDown(KEY_RIGHT)) {
            if (cursorTick == 0) cursorX += 1;
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
    if (IsKeyDown(KEY_NULL)) cursor.set<Tick>({0, cursorMaxTick});

    BeginDrawing();
    ClearBackground(COLOR0);

    BeginMode2D(this->view.camera);
    this->view.drawFloor(this->floorQuery);
    this->view.drawStartEnd(this->model.world);
    this->view.drawCursor(this->model.world.lookup("Cursor"));
    EndMode2D();

    EndDrawing();
}
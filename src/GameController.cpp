#include <raylib.h>
#include <flecs.h>
#include "flecs_ids.hpp"
#include "GameController.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
#include "colors.hpp"


GameController::GameController() : model(0) {
    this->floorQuery = this->model.world.query<FloorTag, Position>();
}
GameController::~GameController() {}
void GameController::run() {
    BeginDrawing();
    ClearBackground(COLOR0);
    BeginMode2D(this->view.camera);
        this->view.drawFloor(this->floorQuery);
    EndMode2D();
    EndDrawing();
}
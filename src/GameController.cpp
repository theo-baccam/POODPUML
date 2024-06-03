#include <raylib.h>
#include <flecs.h>
#include "GameController.hpp"
#include "GameModel.hpp"
#include "colors.hpp"


GameController::GameController() : model(0) {}
GameController::~GameController() {}
void GameController::run() {
    BeginDrawing();
    ClearBackground(COLOR0);
    EndDrawing();
}
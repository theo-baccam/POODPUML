#include <raylib.h>
#include "GameController.hpp"
#include "colors.hpp"


GameController::GameController() {}
GameController::~GameController() {}
void GameController::run() {
    BeginDrawing();
    ClearBackground(COLOR0);
    EndDrawing();
}
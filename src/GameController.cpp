#include <raylib.h>
#include "GameController.hpp"


GameController::GameController() {}
GameController::~GameController() {}
void GameController::run() {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}
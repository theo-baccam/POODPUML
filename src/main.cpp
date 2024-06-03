#include <raylib.h>
#include "Core.hpp"
#include "GameController.hpp"

int main() {
    InitWindow(768, 768, "Tower Defense");
    SetTargetFPS(60);

    Core *core = new Core(new GameController);

    while (!WindowShouldClose()) {
        core->currentController->run();
    };

    return 0;
}
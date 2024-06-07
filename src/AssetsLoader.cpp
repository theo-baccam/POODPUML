#include <raylib.h>
#include <AssetsLoader.hpp>


AssetsLoader::AssetsLoader() {
    this->floorTileTexture = LoadTexture("assets/floor-tile.png");
    this->pathTileTexture = LoadTexture("assets/path-tile.png");
    this->startTexture = LoadTexture("assets/start.png");
    this->endTexture = LoadTexture("assets/end.png");
    this->cursorTexture = LoadTexture("assets/cursor.png");
}
AssetsLoader::~AssetsLoader() {
    UnloadTexture(this->floorTileTexture);
    UnloadTexture(this->pathTileTexture);
    UnloadTexture(this->startTexture);
    UnloadTexture(this->endTexture);
    UnloadTexture(this->cursorTexture);
}
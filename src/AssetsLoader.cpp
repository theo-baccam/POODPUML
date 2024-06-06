#include <raylib.h>
#include <AssetsLoader.hpp>


AssetsLoader::AssetsLoader() {
    this->floorTileTexture = LoadTexture("assets/floor-tile.png");
    this->startTexture = LoadTexture("assets/start.png");
    this->endTexture = LoadTexture("assets/end.png");
}
AssetsLoader::~AssetsLoader() {
    UnloadTexture(this->floorTileTexture);
}
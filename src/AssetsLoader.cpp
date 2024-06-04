#include <raylib.h>
#include <AssetsLoader.hpp>


AssetsLoader::AssetsLoader() {
    this->floorTileTexture = LoadTexture("assets/floor-tile.png");
}
AssetsLoader::~AssetsLoader() {
    UnloadTexture(this->floorTileTexture);
}
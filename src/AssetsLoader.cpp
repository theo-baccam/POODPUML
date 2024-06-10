#include <raylib.h>
#include <AssetsLoader.hpp>

// Constructor for the AssetsLoader class
AssetsLoader::AssetsLoader() {
    // Load textures from the assets directory
    this->floorTileTexture = LoadTexture("assets/floor-tile.png"); // Load floor tile texture
    this->pathTileTexture = LoadTexture("assets/path-tile.png"); // Load path tile texture
    this->startTexture = LoadTexture("assets/start.png"); // Load start texture
    this->endTexture = LoadTexture("assets/end.png"); // Load end texture
    this->cursorTexture = LoadTexture("assets/cursor.png"); // Load cursor texture
}
// Destructor for the AssetsLoader class
AssetsLoader::~AssetsLoader() {
    // Unload textures to free up memory
    UnloadTexture(this->floorTileTexture); // Unload floor tile texture
    UnloadTexture(this->pathTileTexture); // Unload path tile texture
    UnloadTexture(this->startTexture); // Unload start texture
    UnloadTexture(this->endTexture); // Unload end texture
    UnloadTexture(this->cursorTexture); // Unload cursor texture
}
#pragma once
#include <raylib.h>

class AssetsLoader {
    public:
        AssetsLoader();
        ~AssetsLoader();

        Texture2D floorTileTexture;
        Texture2D startTexture;
        Texture2D endTexture;
};
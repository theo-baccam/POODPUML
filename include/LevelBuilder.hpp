#pragma once
#include <flecs.h>


class LevelBuilder {
    public:
        LevelBuilder();
        ~LevelBuilder();

        void buildEasyLevel(flecs::world &world);
};
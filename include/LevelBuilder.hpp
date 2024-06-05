#pragma once
#include <flecs.h>


class LevelBuilder {
    public:
        LevelBuilder();
        ~LevelBuilder();

        void buildEasyLevel(flecs::world &world);
        void buildMediumLevel(flecs:: world &world);
        void buildHardLevel(flecs:: world &world);
};
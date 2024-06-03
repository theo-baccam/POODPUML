#pragma once
#include <flecs.h>
#include "flecs_ids.hpp"
#include "ControllerInterface.hpp"
#include "GameModel.hpp"


class GameController : public ControllerInterface {
    public:
        GameController();
        ~GameController();

        GameModel model;

        flecs::query<FloorTag> floorQuery;

        void run() override;
};
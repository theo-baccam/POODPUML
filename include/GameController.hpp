#pragma once
#include <flecs.h>
#include "flecs_ids.hpp"
#include "ControllerInterface.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"


class GameController : public ControllerInterface {
    public:
        GameController();
        ~GameController();

        GameModel model;
        GameView view;

        flecs::query<FloorTag, Position> floorQuery;

        void run() override;
};
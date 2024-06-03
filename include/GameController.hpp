#pragma once
#include "ControllerInterface.hpp"
#include "GameModel.hpp"


class GameController : public ControllerInterface {
    public:
        GameController();
        ~GameController();

        GameModel model;

        void run() override;
};
#pragma once
#include "ControllerInterface.hpp"


class GameController : public ControllerInterface {
    public:
        GameController();
        ~GameController();

        void run() override;
};
#pragma once
#include "ControllerInterface.hpp"


class Core {
    public:
        Core(ControllerInterface* currentController);
        ~Core();

        ControllerInterface* currentController;

        void switchController(ControllerInterface* newController);
};

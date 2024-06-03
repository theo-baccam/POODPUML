#include <raylib.h>
#include "Core.hpp"
#include "ControllerInterface.hpp"


Core::Core(ControllerInterface* currentController) : currentController(currentController) {}
Core::~Core() {
    delete currentController;
}

void Core::switchController(ControllerInterface* newController) {
    delete currentController;
    currentController = newController;
}

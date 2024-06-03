#pragma once
#include <string>


class ControllerInterface {
    public:
        ControllerInterface();

        std::string nextControllerString;

        virtual ~ControllerInterface() = 0;
        virtual void run() = 0;
};

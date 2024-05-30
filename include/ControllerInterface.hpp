#pragma once


class ControllerInterface {
    public:
        ControllerInterface();
        virtual ~ControllerInterface() = 0;
        virtual void run() = 0;
};

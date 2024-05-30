#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <string>
#include <doctest.h>
#include "Core.hpp"
#include "ControllerInterface.hpp"


class FirstView {
    public:
        FirstView() {};
        ~FirstView() {};
        int getNum(int num) {
            return num;
        }
};

class FirstModel {
    public:
        FirstModel() {};
        ~FirstModel() {};
        int num = 21;
};

class FirstController : public ControllerInterface {
    public:
        FirstController() {};
        ~FirstController() {};

        FirstView view;
        FirstModel model;

        void run() override {
            std::cout << this->view.getNum(this->model.num) << '\n';
        }
};


class SecondView {
    public:
        SecondView() {};
        ~SecondView() {};

        std::string getText(std::string text) {
            return text;
        }
};

class SecondModel {
    public:
        SecondModel() {};
        ~SecondModel() {};

        std::string text = "testing...";
};

class SecondController : public ControllerInterface {
    public:
        SecondController() {};
        ~SecondController() {};

        SecondView view;
        SecondModel model;

        void run() override {
            std::cout << this->view.getText(this->model.text) << '\n';
        }
};


TEST_CASE("Working Core and Controller classes") {
    Core core(new FirstController);

    SUBCASE("Running the current controller") {
        core.currentController->run();
    }

    SUBCASE("Switching the current controller") {
        core.switchController(new SecondController);
        core.currentController->run();
    }
}
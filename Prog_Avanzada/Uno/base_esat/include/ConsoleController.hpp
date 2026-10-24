#pragma once
#ifndef CONSOLE_CONTROLLER_H
#define CONSOLE_CONTROLLER_H

#include "interfaces/IController.hpp"
#include "ConsoleView.hpp"
#include "Model.hpp"

class ConsoleController : public IController{
    public:
        void run() override;
    private:
        ConsoleView view_;
        Model model_;

    void prepareMatch();
};

#endif
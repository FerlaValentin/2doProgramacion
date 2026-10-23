#pragma once
#ifndef CONSOLE_CONTROLLER_H
#define CONSOLE_CONTROLLER_H

#include "IController.hpp"

class ConsoleController : public IController{
    public:
        void run() override;
};

#endif
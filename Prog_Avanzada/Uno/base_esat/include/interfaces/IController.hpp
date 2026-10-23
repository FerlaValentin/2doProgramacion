#pragma once
#ifndef UNO_INTERFACES_ICONTROLLER_HPP
#define UNO_INTERFACES_ICONTROLLER_HPP

class IController {
    public:
        virtual ~IController() = default;
        virtual void run() = 0;
};

#endif // UNO_INTERFACES_ICONTROLLER_HPP

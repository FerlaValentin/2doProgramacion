#pragma once
#ifndef UNO_INTERFACES_IVIEW_HPP
#define UNO_INTERFACES_IVIEW_HPP

#include "BoolAction.hpp"
#include "Color.hpp"
#include "ICard.hpp"

class IView {
    public:
    virtual ~IView() = default;
    virtual void print() const =0;

    virtual void update() =0;

    // Tiene que tener opcion nula
    virtual BoolAction pass() const = 0;
    virtual ICard* cardSelected() const =0;
    virtual bool drawWanted() const =0;
    virtual Color colorSelected() const =0;
    virtual BoolAction unoSaid() const =0;
    virtual bool accuseUno() const =0;
    virtual BoolAction wantChallenge() const =0;

    virtual void clearSelections() = 0;
};

#endif // UNO_INTERFACES_IVIEW_HPP

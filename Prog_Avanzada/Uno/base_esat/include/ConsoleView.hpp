#pragma once
#ifndef CONSOLE_VIEW_HPP
#define CONSOLE_VIEW_HPP

#include "interfaces/IView.hpp"

namespace std{
    typedef basic_string<char> string;
    template<typename T> class optional{};
}

class ConsoleView : public IView {
    public:
        void print() const override{};

        void update() override{};

        // Tiene que tener opcion nula
        BoolAction pass() const override{ return BoolAction::Null;};
        ICard* cardSelected() const override{ return nullptr;};
        bool drawWanted() const override{ return false;};
        Color colorSelected() const override{return Color::Null;};
        BoolAction unoSaid() const override{return BoolAction::Null;};
        bool accuseUno() const override{ return false;};
        BoolAction wantChallenge() const override{return BoolAction::Null;};

        void clearSelections() override{};

        void printUNO() const;
        void askNumPlayer() const;
        std::optional<std::string> readTextInput();
        std::optional<int> readIntegerInput();

    private:
        std::string input_;
};

#endif

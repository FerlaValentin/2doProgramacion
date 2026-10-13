#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <windows.h>
#include "tictactoe.hpp"

class GameFlow{
    public:
        void run();

        GameFlow():
        x_{-1},
        y_{-1},
        ttt_{cellsPerCol_},
        cxy_{0, 0}
        {
            for(int slot = 0; slot < buffer_capacity_; slot++)
                buffer_[slot] = '\0';
        }

    private:
        static constexpr unsigned char cellsPerCol_ = 3, maxCells_ = cellsPerCol_ * cellsPerCol_, boardWidth_ = cellsPerCol_ * 4 - 1, buffer_capacity_ = 4;
        char buffer_[buffer_capacity_], x_, y_;
        Tictactoe ttt_ = Tictactoe(cellsPerCol_);
        COORD cxy_;

        void printBoard() const;
        void printCurrPlayer() const;
        void AssignInputCoords();
        void askPlayer();
        void assignCoordsFromBuffer();
        void resetBuffer();
        void printBadPlay() const;
        void printWinner() const;
        void refreshScreen() const;
        void printInvalidFormat();
};

#endif
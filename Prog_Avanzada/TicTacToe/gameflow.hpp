#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include "tictactoe.hpp"

class GameFlow{
    public:
        void run();

    private:
        static constexpr unsigned char cellsPerCol_ = 3, maxCells_ = cellsPerCol_ * cellsPerCol_, boardWidth_ = cellsPerCol_ * 4 - 1;
        Tictactoe ttt_ = Tictactoe(cellsPerCol_);

        void printBoard() const;
        void askPlayer(int& x, int& y, char buffer[]) const;
        void printBadPlay() const;
        void printWinner() const;
        void refreshScreen() const;
        void printCurrPlayer() const;
};

#endif
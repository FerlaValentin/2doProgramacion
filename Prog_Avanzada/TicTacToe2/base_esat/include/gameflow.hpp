#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <windows.h>

#ifdef DrawText
#undef DrawText
#endif

#include "tictactoe.hpp"

class IGameFlow{
    public:
        virtual void run() = 0;
        virtual ~IGameFlow() = default;
    protected:
        static constexpr unsigned char cellsPerCol_ = 3;
        Tictactoe ttt_ = Tictactoe(cellsPerCol_);

        virtual void printBoard() const = 0;
        virtual void printCurrPlayer() const = 0;
        virtual void askPlayer() = 0;
        virtual void printBadPlay() const = 0;
        virtual void printWinner() const = 0;
};

class ConsoleGameFlow : public IGameFlow{
    public:
        void run() override;

        ConsoleGameFlow():
        x_{-1},
        y_{-1},
        cxy_{0, 0}
        {
            for(int slot = 0; slot < buffer_capacity_; slot++)
                buffer_[slot] = '\0';
        }

    private:
        static constexpr unsigned char maxCells_ = cellsPerCol_ * cellsPerCol_, boardWidth_ = cellsPerCol_ * 4 - 1, buffer_capacity_ = 4;
        char buffer_[buffer_capacity_], x_, y_;
        COORD cxy_;

        void printBoard() const override;
        void refreshScreen() const;
        void printCurrPlayer() const override;
        void AssignInputCoords();
        void printInvalidFormat();
        void assignCoordsFromBuffer();
        void askPlayer() override;
        void resetBuffer();
        void printBadPlay() const override;
        void printWinner() const override;
};

class GraphicGameFlow : public IGameFlow{
    public:
        void run() override;

        GraphicGameFlow(short screen_x, short screen_y):
        SCREEN_X_{screen_x},
        SCREEN_Y_{screen_y},
        EVENT_LOG_HEIGHT_{SCREEN_Y_ / 4.0f * 3}
        {}
    private:
        static constexpr unsigned char CELL_SIDE_LENGTH_X = 100;
        const short SCREEN_X_, SCREEN_Y_;
        const float EVENT_LOG_HEIGHT_;

        void printBoard() const override;
        void printCurrPlayer() const override;
        void askPlayer() override;
        void printBadPlay() const override;
        void printWinner() const override;
};

#endif
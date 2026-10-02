#pragma once

enum class Ficha : char{
    X = 'X',
    O = 'O',
    Vacio = ' '
};

class Tictactoe {
    public:
        static constexpr int cellsPerCol = 3, maxCells = cellsPerCol * cellsPerCol, boardWidth = cellsPerCol * 4 - 1;

        Tictactoe(){
            for(int cell = 0; cell < maxCells; cell++)  celdas[cell] = Ficha::Vacio;
        };
        bool play(int x, int y);

        // OBSERVACION
        Ficha winCondition() const;
        bool isGameEnded() const;
        int turn() const;
        Ficha nextPlayer() const;
        Ficha getCell(int x, int y) const {return celdas[y * cellsPerCol + x];};

    private:
        Ficha celdas[maxCells];
};

void printBoard(const Tictactoe& ttt);
void askPlayer(const Tictactoe& ttt, int& x, int& y);
void printBadPlay(const Tictactoe& ttt, int x, int y);
void printWinner(const Tictactoe& ttt);
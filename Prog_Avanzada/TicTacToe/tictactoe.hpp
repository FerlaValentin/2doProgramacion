#pragma once

#include <cstdlib>

enum class Ficha : char{
    X = 'X',
    O = 'O',
    Vacio = ' '
};

class Tictactoe {
    public:
        Tictactoe(int cellsPerCol):
            cellsPerCol_{cellsPerCol},
            maxCells_{cellsPerCol_ * cellsPerCol_}
        {
            celdas = (Ficha*)malloc(sizeof(Ficha) * maxCells_);
            for(int cell = 0; cell < maxCells_; cell++)  celdas[cell] = Ficha::Vacio;
        };
        bool play(int x, int y);

        // OBSERVACION
        Ficha winCondition() const;
        bool isGameEnded() const;
        int turn() const;
        Ficha nextPlayer() const;
        Ficha getCell(int x, int y) const {return celdas[y * cellsPerCol_ + x];};

    private:
        const unsigned char cellsPerCol_;
        const unsigned char maxCells_;
        Ficha* celdas;
};
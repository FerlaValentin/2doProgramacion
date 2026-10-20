#include "GameFlow.hpp"

#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <string.h>

#include <esat\draw.h>
#include <esat\input.h>
#include <esat\math.h>

namespace{
    void printSeparator(int boardWidth){
        for(int i = 0; i < boardWidth; i++) printf("=");
        printf("\n");
    }

    void printRow(const Tictactoe& ttt, int row_index, int boardWidth, int cellsPerCol){
        for(int row_char = 0; row_char < boardWidth; row_char++){
            if(row_char % 2){
                if(row_char % 4 % 3 == 0)
                    printf("|");
                else{
                    const unsigned char col_index = row_char / 4;

                    printf("%c", static_cast<char>(ttt.getCell(col_index, row_index)));
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }

    int GetFirstBufferEmptySlot(char buffer[], int capacity){
        int slot = 0;

        for(slot; slot < capacity; ++slot)
            if(buffer[slot] == '\0') break;
        
        return slot;
    }

    bool IsAnEnterKey(char pressed_key){
        return pressed_key == 10 || pressed_key == 13;
    }

    bool IsBufferFull(int first_free_slot, int letters_capacity){
        return first_free_slot == letters_capacity;
    }

    bool IsANumber(char buffer_slot){
        return buffer_slot >= '0' && buffer_slot <= '9';
    }

    void DeleteLastCharacterFromConsole(){
        constexpr char SPACE_ASCII_VALUE = 32, BACKSPACE_ASCII_VALUE = 8;
        printf("%c%c%c", BACKSPACE_ASCII_VALUE, SPACE_ASCII_VALUE, BACKSPACE_ASCII_VALUE);
    }

    int TranslateNumCharToInt(char number){
        return number - '0';
    }

    bool IsInputValid(char buffer[], int cells_per_col){
        constexpr char SPACE_ASCII_VALUE = 32;

        return IsANumber(buffer[0]) && buffer[1] == SPACE_ASCII_VALUE && IsANumber(buffer[2]);
    }
}

void ConsoleGameFlow::printBoard() const{
    for(int row = 0; row < cellsPerCol_; ++row){
        printSeparator(boardWidth_);
        printRow(ttt_, row, boardWidth_, cellsPerCol_);
    }
    printSeparator(boardWidth_);
}

void ConsoleGameFlow::refreshScreen() const{
    system("cls");
    printBoard();
}

void ConsoleGameFlow::printCurrPlayer() const{
    printf("Jugador %c: ", static_cast<char>(ttt_.nextPlayer()));
}

void ConsoleGameFlow::AssignInputCoords(){
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    cxy_.X = csbiInfo.dwCursorPosition.X;
    cxy_.Y = csbiInfo.dwCursorPosition.Y;
}

void ConsoleGameFlow::printInvalidFormat(){
    refreshScreen();
    printCurrPlayer();
    printf("\nInvalid input. Correct format is \"[X] [Y]\"\n");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy_);
    resetBuffer();
}

void ConsoleGameFlow::askPlayer(){
    if(_kbhit()){
        constexpr char SPACE_ASCII_VALUE = 32, BACKSPACE_ASCII_VALUE = 8;
        unsigned char first_free_slot = GetFirstBufferEmptySlot(buffer_, buffer_capacity_);
        char pressed_key = _getch();

        if(IsAnEnterKey(pressed_key)){
            if(IsBufferFull(first_free_slot, buffer_capacity_ - 1))
                buffer_[buffer_capacity_ - 1] = pressed_key;
            else
                printInvalidFormat();
        }
        else{
            if(!IsBufferFull(first_free_slot, buffer_capacity_ - 1)){
                if(IsANumber(pressed_key) || pressed_key == SPACE_ASCII_VALUE){
                    printf("%c", pressed_key);
                    buffer_[first_free_slot] = pressed_key;
                }
            }
            if(pressed_key == BACKSPACE_ASCII_VALUE && first_free_slot){
                DeleteLastCharacterFromConsole();
                buffer_[first_free_slot - 1] = '\0';
            }
        }
    }
}

void ConsoleGameFlow::assignCoordsFromBuffer(){
    x_ = TranslateNumCharToInt(buffer_[0]);
    y_ = TranslateNumCharToInt(buffer_[2]);
}

void ConsoleGameFlow::printBadPlay() const{
    printf("\nInvalid play. Try again\n");
}

void ConsoleGameFlow::resetBuffer(){
    for(int slot = 0; slot < buffer_capacity_; ++slot)
    buffer_[slot] = '\0';
}

void ConsoleGameFlow::printWinner() const{
    switch(ttt_.winCondition()){
        case Ficha::X: printf("Player X wins!"); break;
        case Ficha::O: printf("Player O wins!"); break;
        case Ficha::Vacio: printf("Tie"); break;
    }
}

void ConsoleGameFlow::run(){
    refreshScreen();
    printCurrPlayer();
    AssignInputCoords();
    while(!ttt_.isGameEnded()) {
        askPlayer();
        if(IsAnEnterKey(buffer_[buffer_capacity_ - 1])){
            if(IsInputValid(buffer_, cellsPerCol_)){
                assignCoordsFromBuffer();
                if(!ttt_.play(x_,y_)){
                    refreshScreen();
                    printCurrPlayer();
                    printBadPlay();
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cxy_);
                }
                else{
                    refreshScreen();
                    if(!ttt_.isGameEnded()) printCurrPlayer();
                }
                resetBuffer();
            }
            else
                printInvalidFormat();
        }
    }
    printWinner();
}

namespace{
    void DrawSeparator(short screen_x, float separator_height){
        esat::DrawSetStrokeColor(143, 0, 255);
        esat::DrawLine(0.0f, separator_height, screen_x, separator_height);
    }

    void DrawCells(short screen_x, float separator_height){
        esat::DrawSetStrokeColor(255, 255, 255);
        esat::DrawLine(0.0f, separator_height / 3, screen_x, separator_height / 3);
        esat::DrawLine(0.0f, separator_height / 3 * 2, screen_x, separator_height / 3 * 2);
        esat::DrawLine(screen_x / 3.0f, 0.0f, screen_x / 3.0f, separator_height);
        esat::DrawLine(screen_x / 3.0f * 2, 0.0f, screen_x / 3.0f * 2, separator_height);
    }

    void DrawTile(const Tictactoe& ttt, unsigned char cells_per_col, short screen_x, float separator_height){
        const short screen_x_third = screen_x / 3;
        const float separator_height_third = separator_height / 3;

        esat::DrawSetTextSize(50.0f);
        for(int y = 0; y < cells_per_col; ++y){
            for(int x = 0; x < cells_per_col; ++x){
                char tile[2] = {static_cast<char>(ttt.getCell(x, y)), '\0'};

                esat::DrawSetFillColor(255,255,255);
                esat::DrawText(screen_x_third * x + screen_x_third * 0.45f, separator_height_third * y + separator_height_third * 0.65f, tile);
            }
        }
        esat::DrawSetTextSize(30.0f);
    }
    
    bool IsMouseOverBoard(short screen_x, float event_log_height){
        esat::Vec2 mouse_pos = {(float)esat::MousePositionX(), (float)esat::MousePositionY()};

        return mouse_pos.x >= 0 && mouse_pos.x <= screen_x
            && mouse_pos.y >= 0 && mouse_pos.y <= event_log_height;
    }
    
    esat::Vec2 GetHoveredCell(esat::Vec2 mouse_pos, short screen_x, float event_log_height){
        const short screen_x_third = screen_x / 3;
        const float log_height_third = event_log_height / 3;
        
        return {(float)((int)mouse_pos.x / screen_x_third), (float)((int)mouse_pos.y / (int)log_height_third)};
    }

    void PaintHoveredCell(esat::Vec2 cell_pos, short screen_x, float event_log_height){
        const short screen_x_third = screen_x / 3;
        const float log_height_third = event_log_height / 3;
        const esat::Vec2 top_left_cell = {screen_x_third * cell_pos.x, log_height_third * cell_pos.y},
                    bottom_right_cell = {screen_x_third * (cell_pos.x + 1), log_height_third * (cell_pos.y + 1)};

        esat::Vec2 cell_points[4] = {{top_left_cell.x, top_left_cell.y}
                                    ,{bottom_right_cell.x, top_left_cell.y}
                                    ,{bottom_right_cell.x, bottom_right_cell.y}
                                    ,{top_left_cell.x, bottom_right_cell.y}};

        esat::DrawSetFillColor(255,255,0,127);
        esat::DrawSolidPath(&cell_points->x, 4, false);
    }

    bool IsCellEmpty(esat::Vec2 cell_pos, const Tictactoe& ttt){
        return ttt.getCell((int)cell_pos.x, (int)cell_pos.y) == Ficha::Vacio;
    }

    bool HasACellBeenClicked(int x, int y){
        return x != -1 && y != -1;
    }

    void DrawConclusionText(char text[], unsigned char r, unsigned char g, unsigned char b, short screen_x, short screen_y, float separator_height){
        const float EVENT_LOG_MID = (screen_y + separator_height) / 2;

        esat::DrawSetFillColor(r,g,b);
        esat::DrawText(screen_x / 2.75f, EVENT_LOG_MID, text);
    }
}

void GraphicGameFlow::printBoard() const{
    DrawSeparator(SCREEN_X_, EVENT_LOG_HEIGHT_);
    DrawCells(SCREEN_X_, EVENT_LOG_HEIGHT_);
    DrawTile(ttt_, cellsPerCol_, SCREEN_X_, EVENT_LOG_HEIGHT_);
}

void GraphicGameFlow::printCurrPlayer() const{
    const float EVENT_LOG_MID = (SCREEN_Y_ + EVENT_LOG_HEIGHT_) / 2;
    char turn_text[9] = {'P','l','a','y','e','r',' ',static_cast<char>(ttt_.nextPlayer()), '\0'};

    esat::DrawSetFillColor(255,255,0);
    esat::DrawText(SCREEN_X_ / 2.75f, EVENT_LOG_MID, turn_text);
}

void GraphicGameFlow::askPlayer(){
    if(IsMouseOverBoard(SCREEN_X_, EVENT_LOG_HEIGHT_)){
        esat::Vec2 mouse_pos = {(float)esat::MousePositionX(), (float)esat::MousePositionY()},
                    cell_pos = GetHoveredCell(mouse_pos, SCREEN_X_, EVENT_LOG_HEIGHT_);

        PaintHoveredCell(cell_pos, SCREEN_X_, EVENT_LOG_HEIGHT_);
        if(esat::MouseButtonDown(0)){
            x_ = (char)cell_pos.x;
            y_ = (char)cell_pos.y;
        }
    }
}

void GraphicGameFlow::printBadPlay() const{
    const float PLAYER_TEXT_POS = (SCREEN_Y_ + EVENT_LOG_HEIGHT_) / 2;
    
    esat::DrawSetTextSize(20.0f);
    esat::DrawSetFillColor(255,0,0);
    esat::DrawText(SCREEN_X_ * 0.25f, PLAYER_TEXT_POS + 30, "TAKEN CELL. PICK ANOTHER ONE");
    esat::DrawSetTextSize(30.0f);
}

void GraphicGameFlow::printWinner() const{
    esat::DrawSetTextSize(40.0f);
    switch(ttt_.winCondition()){
        case Ficha::X:
        case Ficha::O: {
            char winner_text[15] = {'P','l','a','y','e','r',' ',static_cast<char>(ttt_.winCondition()),' ','w','i','n','s','!','\0'};

            DrawConclusionText(winner_text, 0, 255, 0, SCREEN_X_, SCREEN_Y_, EVENT_LOG_HEIGHT_);
            break;
        }
        case Ficha::Vacio: {
            char tie_text[] = "Tie!";

            DrawConclusionText(tie_text, 255, 255, 255, SCREEN_X_, SCREEN_Y_, EVENT_LOG_HEIGHT_);
            break;
        }
        default: {
            char error[] = "ERROR";

            DrawConclusionText(error, 255, 0, 0, SCREEN_X_, SCREEN_Y_, EVENT_LOG_HEIGHT_);
            break;
        }
    }
}

void GraphicGameFlow::run(){
    GraphicGameFlow::printBoard();
    if(!ttt_.isGameEnded()){
        GraphicGameFlow::printCurrPlayer();
        GraphicGameFlow::askPlayer();
        if(HasACellBeenClicked(x_, y_)) was_last_move_bad_ = !ttt_.play(x_, y_);
        if(was_last_move_bad_)  GraphicGameFlow::printBadPlay();
    }
    else
        GraphicGameFlow::printWinner();
}
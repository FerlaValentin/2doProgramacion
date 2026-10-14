#include "menu.hpp"

void Menu::DrawSprites(short screen_x){
    st_.x = (float)screen_x / 4;
    esat::DrawSprite(cmd_sprite_, st_);
    st_.x = (float)screen_x / 4 * 2;
    esat::DrawSprite(graphic_sprite_, st_);
}

void Menu::Run(short screen_x){
    DrawSprites(screen_x);
}
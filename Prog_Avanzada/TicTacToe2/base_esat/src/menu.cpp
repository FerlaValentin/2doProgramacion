#include "menu.hpp"

#include <esat\input.h>

void Menu::DrawSprites() const{
    esat::DrawSprite(cmd_sprite_, cmd_st_);
    esat::DrawSprite(graphic_sprite_, graphic_st_);
}

void Menu::Run(){
    DrawSprites();
}
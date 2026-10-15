#include "menu.hpp"

#include <cstdio>
#include <esat\input.h>
#include <esat\math.h>
#include <esat\draw.h>

bool Menu::CheckHovering(const TSpriteConfig& sprite) const{
    bool inside_x = false, inside_y = false;
    const esat::Vec2 half_real_proportions = {esat::SpriteWidth(sprite.sprite) * sprite.st.scale_x * 0.5f,
                esat::SpriteHeight(sprite.sprite) * sprite.st.scale_y * 0.5f},
                mouse = {esat::MousePositionX(), esat::MousePositionY()};

    inside_x = sprite.st.x - half_real_proportions.x <= mouse.x && mouse.x <= sprite.st.x + half_real_proportions.x;
    inside_y = sprite.st.y - half_real_proportions.y <= mouse.y && mouse.y <= sprite.st.y + half_real_proportions.y;

    return inside_x && inside_y;
}

void Menu::DrawHoverBackground(const TSpriteConfig& sprite) const{
    const esat::Vec2 half_real_proportions = {esat::SpriteWidth(sprite.sprite) * sprite.st.scale_x * 0.5f,
                esat::SpriteHeight(sprite.sprite) * sprite.st.scale_y * 0.5f};
    esat::Vec2 bg_points[4] = {{sprite.st.x - half_real_proportions.x, sprite.st.y - half_real_proportions.y},
                {sprite.st.x + half_real_proportions.x, sprite.st.y - half_real_proportions.y},
                {sprite.st.x + half_real_proportions.x, sprite.st.y + half_real_proportions.y},
                {sprite.st.x - half_real_proportions.x, sprite.st.y + half_real_proportions.y}};
    
    esat::DrawSetFillColor(255,255,255);
    esat::DrawSolidPath(&bg_points->x, 4, false);
}

void Menu::DrawSprite(const TSpriteConfig& sprite) const {
    if(CheckHovering(sprite)){
        Menu::DrawHoverBackground(sprite);
        esat::DrawSprite(sprite.hovered_sprite, sprite.st);
    }
    else
        esat::DrawSprite(sprite.sprite, sprite.st);
    
}

Screens Menu::SelectOption() const{
    if(esat::MouseButtonDown(0)){
        if(CheckHovering(cmd_sprite_)) return Screens::CMDScreen;
        if(CheckHovering(graphic_sprite_)) return Screens::GraphicScreen;
    }

    return Screens::MenuScreen;
}

Screens Menu::Run(){
    DrawSprite(cmd_sprite_);
    DrawSprite(graphic_sprite_);
    return SelectOption();
}
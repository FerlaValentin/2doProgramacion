#ifndef MENU_H
#define MENU_H

#include <esat\sprite.h>

class Menu{
    public:
        Menu(short screen_x, short screen_y){
            cmd_sprite_ = esat::SpriteFromFile("./../data/cmd_sprite.png");
            graphic_sprite_ = esat::SpriteFromFile("./../data/graphic_sprite.png");

            esat::SpriteTransformInit(&cmd_st_);
            esat::SpriteTransformInit(&graphic_st_);

            cmd_st_.scale_x = 0.5f;
            cmd_st_.scale_y = 0.5f;
            graphic_st_.scale_x = 0.05f;
            graphic_st_.scale_y = 0.05f;

            cmd_st_.sprite_origin_x = esat::SpriteWidth(cmd_sprite_) / 2.0f;
            cmd_st_.sprite_origin_y = esat::SpriteHeight(cmd_sprite_) / 2.0f;
            graphic_st_.sprite_origin_x = esat::SpriteWidth(graphic_sprite_) / 2.0f;
            graphic_st_.sprite_origin_y = esat::SpriteHeight(graphic_sprite_) / 2.0f;

            cmd_st_.x = screen_x / 4.0f;
            graphic_st_.x = screen_x / 4.0f * 3;
            cmd_st_.y = screen_y / 2.0f;
            graphic_st_.y = screen_y / 2.0f;
        }

        ~Menu(){
            esat::SpriteRelease(cmd_sprite_);
            esat::SpriteRelease(graphic_sprite_);
        }

        void Run();
    private:
        esat::SpriteHandle cmd_sprite_, graphic_sprite_;
        esat::SpriteTransform cmd_st_, graphic_st_;

        void DrawSprites() const;
};

#endif
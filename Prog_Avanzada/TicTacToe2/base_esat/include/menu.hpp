#ifndef MENU_H
#define MENU_H

#include <esat\sprite.h>

class Menu{
    public:
        Menu(short screen_y){
            cmd_sprite_ = esat::SpriteFromFile("./../data/cmd_sprite.png");
            //graphic_sprite_ = esat::SpriteFromFile("./../data/graphic_sprite.webp");
            esat::SpriteTransformInit(&st_);
            st_.sprite_origin_x = 0.5f;
            st_.sprite_origin_y = 0.5f;
            st_.y = (float)screen_y / 2;
        }

        ~Menu(){
            esat::SpriteRelease(cmd_sprite_);
            //esat::SpriteRelease(graphic_sprite_);
        }

        void Run(short screen_x);
    private:
        esat::SpriteHandle cmd_sprite_, graphic_sprite_;
        esat::SpriteTransform st_;

        void DrawSprites(short screen_x);
};

#endif
#ifndef MENU_H
#define MENU_H

#include <esat\sprite.h>

enum class Screens{
  MenuScreen,
  GraphicScreen,
  CMDScreen
};

struct TSpriteConfig{
    esat::SpriteHandle sprite, hovered_sprite;
    esat::SpriteTransform st;
};

class Menu{
    public:
        Menu(short screen_x, short screen_y){
            cmd_sprite_.sprite = esat::SpriteFromFile("./../data/cmd_sprite.png");
            graphic_sprite_.sprite = esat::SpriteFromFile("./../data/graphic_sprite.png");
            cmd_sprite_.hovered_sprite = esat::SpriteFromFile("./../data/hovered_cmd_sprite.png");
            graphic_sprite_.hovered_sprite = esat::SpriteFromFile("./../data/hovered_graphic_sprite.png");

            esat::SpriteTransformInit(&cmd_sprite_.st);
            esat::SpriteTransformInit(&graphic_sprite_.st);

            cmd_sprite_.st.scale_x = 0.5f;
            cmd_sprite_.st.scale_y = 0.5f;
            graphic_sprite_.st.scale_x = 0.05f;
            graphic_sprite_.st.scale_y = 0.05f;

            cmd_sprite_.st.sprite_origin_x = esat::SpriteWidth(cmd_sprite_.sprite) / 2.0f;
            cmd_sprite_.st.sprite_origin_y = esat::SpriteHeight(cmd_sprite_.sprite) / 2.0f;
            graphic_sprite_.st.sprite_origin_x = esat::SpriteWidth(graphic_sprite_.sprite) / 2.0f;
            graphic_sprite_.st.sprite_origin_y = esat::SpriteHeight(graphic_sprite_.sprite) / 2.0f;

            cmd_sprite_.st.x = screen_x / 4.0f;
            graphic_sprite_.st.x = screen_x / 4.0f * 3;
            cmd_sprite_.st.y = screen_y / 2.0f;
            graphic_sprite_.st.y = screen_y / 2.0f;
        }

        ~Menu(){
            esat::SpriteRelease(cmd_sprite_.sprite);
            esat::SpriteRelease(graphic_sprite_.sprite);
            esat::SpriteRelease(cmd_sprite_.hovered_sprite);
            esat::SpriteRelease(graphic_sprite_.hovered_sprite);
        }

        Screens Run();
    private:
        TSpriteConfig cmd_sprite_, graphic_sprite_;

        void DrawSprite(const TSpriteConfig& sprite) const;
        bool CheckHovering(const TSpriteConfig& sprite) const;
        void DrawHoverBackground(const TSpriteConfig& sprite) const;
        Screens SelectOption() const;
};

#endif
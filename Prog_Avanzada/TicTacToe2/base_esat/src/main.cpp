#include <esat\window.h>
#include <esat\input.h>
#include <esat\draw.h>

#include "gameflow.hpp"
#include "menu.hpp"

int esat::main(int argc, char **argv) {
  constexpr short SCREEN_X = 640, SCREEN_Y = 480; 
  esat::WindowInit(SCREEN_X, SCREEN_Y);
  esat::WindowSetMouseVisibility(true);
  Menu menu(SCREEN_X, SCREEN_Y);
  Screens curr_screen = Screens::MenuScreen;
  IGameFlow* gf = nullptr;
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && curr_screen != Screens::CMDScreen) {
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    if(curr_screen == Screens::MenuScreen){
      curr_screen = menu.Run();
      if(curr_screen == Screens::GraphicScreen){
        esat::DrawSetTextFont("./../data/Nunito/Nunito-VariableFont_wght.ttf");
        esat::DrawSetTextSize(20.0f);
      }
    }
    if(curr_screen == Screens::GraphicScreen){
      gf = new GraphicGameFlow(SCREEN_X, SCREEN_Y);
      gf->run();
      delete gf;
    }

    esat::DrawEnd();
    esat::WindowFrame();
  }
  esat::WindowDestroy();
  if(curr_screen == Screens::CMDScreen){
    gf = new ConsoleGameFlow();
    gf->run();
    delete gf;
  }

  return 0;
}
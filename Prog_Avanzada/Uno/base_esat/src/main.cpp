#include <esat\window.h>
#include <esat\input.h>
#include <esat\draw.h>

#include "Menu.hpp"
#include "ConsoleController.hpp"

int esat::main(int argc, char **argv) {
  constexpr short SCREEN_X = 640, SCREEN_Y = 480; 
  esat::WindowInit(SCREEN_X, SCREEN_Y);
  esat::WindowSetMouseVisibility(true);
  Menu menu(SCREEN_X, SCREEN_Y);
  Screens curr_screen = Screens::MenuScreen;
  IController* controller = nullptr;
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && curr_screen != Screens::CMDScreen) {
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    if(curr_screen == Screens::MenuScreen){
      curr_screen = menu.Run();
      if(curr_screen == Screens::GraphicScreen){
        //gf = new GraphicGameFlow(SCREEN_X, SCREEN_Y);
        //esat::DrawSetTextFont("./../data/Nunito/static/Nunito-ExtraBold.ttf");
      }
    }
    else{
      if(curr_screen == Screens::GraphicScreen){} //gf->run();
    }

    esat::DrawEnd();
    esat::WindowFrame();
  }
  esat::WindowDestroy();
  if(curr_screen == Screens::CMDScreen){
    controller = new ConsoleController();
    controller->run();
  }
  delete controller;

  return 0;
}
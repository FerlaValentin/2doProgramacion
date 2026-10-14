#include <esat\window.h>
#include <esat\input.h>
#include <esat\draw.h>
#include <esat\sprite.h>

#include "gameflow.hpp"
#include "menu.hpp"

int esat::main(int argc, char **argv) {
  constexpr short SCREEN_X = 640, SCREEN_Y = 480; 
  Menu menu(SCREEN_Y);
  esat::WindowInit(SCREEN_X, SCREEN_Y);
  esat::WindowSetMouseVisibility(true);
  while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    

    esat::DrawEnd();
    esat::WindowFrame();
  }
  esat::WindowDestroy();

  return 0;
}
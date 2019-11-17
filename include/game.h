#ifndef GAME_H
#define GAME_H

#include "SDL.h"

class Game {
 public:
  Game();
  ~Game();
  bool init();
  void run();
  void clean();

 private:
  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  SDL_Window* window;
  SDL_Window* renderer;
};

#endif

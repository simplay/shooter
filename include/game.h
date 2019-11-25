#ifndef GAME_H
#define GAME_H

#include "SDL.h"

class Game {
 public:
  Game();
  ~Game();
  bool init();
  void run();

  /**
   * Draws a vertical line at a given x location ranging from yTop to yBottom.
   *
   * @param x horizontal grid location
   * @param yTop upper vertical grid location
   * @param yBottom lower vertical grid location
   * @param topColor top border color
   * @param fillColor
   * @param bottomColor bottom border color
   */
  void drawVerticalLine(int x, int yTop, int yBottom, int topColor, int fillColor, int bottomColor);

 private:
  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  Uint32* pixels;
};

#endif

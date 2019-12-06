#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL.h"
#include "vec2f.h"

enum Color {
  Red = 0xFF0000,
  Green = 0x00FF00,
  Blue = 0x0000FF,
  Turquoise = 0x00FFFF,
  Yellow = 0xFFFF00,
  White = 0xFFFFFF
};

class Game {
 public:
  Game();
  Game(int mapWidth, int mapHeight);
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

  /**
   * Draws a vertical line at a given x location ranging from yTop to yBottom.
   *
   * @param x horizontal grid location
   * @param yTop upper vertical grid location
   * @param yBottom lower vertical grid location
   * @param color
   */
  void drawVerticalLine(int x, int yTop, int yBottom, int color);

 private:
  // Screen dimension constants
  static const int SCREEN_WIDTH = 640;
  static const int SCREEN_HEIGHT = 480;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  Uint32* pixels;

  std::vector<std::vector<int>> worldMap;

  Uint32 colorAt(int x, int y);
  bool hitWall(int x, int y);
};

#endif

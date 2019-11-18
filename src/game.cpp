#include "game.h"
#include "player.h"
#include "vec3f.h"
#include <iostream>

Game::Game() {
  window = nullptr;
  renderer = nullptr;
}

Game::~Game() {
  std::cout << "Freeing resources.." << std::endl;
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Window *window =
      SDL_CreateWindow("Shooter Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  return true;
}

void Game::run() {
  Vec3f p(1, 2, 3);
  Vec3f v(1, 2, 3);
  Player player(p, v);
  std::cout << player.position.y << std::endl;
  player.position.y = 22.0;
  std::cout << player.position.y << std::endl;

  SDL_Delay(3000);
}

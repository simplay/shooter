#include "game.h"
#include <iostream>

Game::Game() {
  window = nullptr;
  renderer = nullptr;
}

Game::~Game() {}

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

void Game::run() { SDL_Delay(3000); }

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

#include "game.h"
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>
#include "player.h"
#include "sector.h"
#include "vec2f.h"
#include "vec3f.h"

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
  // Init Game-State
  using json = nlohmann::json;
  std::ifstream filestream("../maps/map.json");
  json map;
  filestream >> map;
  // std::cout << map << std::endl;

  float playerX = map["player"]["x"];
  float playerY = map["player"]["y"];

  Vec3f p(playerX, playerY, 3);
  Vec3f v(0, 0, 0);
  Player player(p, v);
  // std::cout << "player pos: ("<< player.position.x << ", " << player.position.y << ")" <<
  // std::endl;

  std::map<int, Vec2f> vertices;
  for (auto vertex : map["vertices"]) {
    int vertexId = vertex["id"];
    float vx = vertex["x"];
    float vy = vertex["y"];
    vertices.emplace(vertexId, Vec2f(vx, vy));
  }

  // for(auto const& entry : vertices) {
  //   std::cout << entry.second.x << " " << entry.second.y << std::endl;
  // }

  std::map<int, Sector> sectors;
  for (auto segment : map["segments"]) {
    int sectorId = segment["id"];
    float floor = segment["floor"];
    float ceil = segment["ceil"];

    std::vector<Vec2f> sectorVertices;
    for (int vertIdx : segment["vertices"]) {
      sectorVertices.push_back(vertices.at(vertIdx));
    }

    sectors.emplace(sectorId, Sector(floor, ceil, sectorVertices));
  }

  // for(auto const& entry : sectors) {
  //   std::cout << entry.second.ceil << " " << entry.second.floor << std::endl;
  // }

  // Init renderer
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

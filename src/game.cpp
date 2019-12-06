#include "game.h"
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>
#include "player.h"
#include "sector.h"
#include "vec2f.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))   // min: Choose smaller of two scalars.
#define max(a, b) (((a) > (b)) ? (a) : (b))   // max: Choose greater of two scalars.
#define clamp(a, mi, ma) min(max(a, mi), ma)  // clamp: Clamp value into set range.

Game::Game() {
  window = nullptr;
  renderer = nullptr;
  texture = nullptr;
  pixels = nullptr;

  worldMap = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
              {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
}

Game::Game(int mapWidth, int mapHeight) {
  window = nullptr;
  renderer = nullptr;
  texture = nullptr;
  pixels = nullptr;

  for (int m = 0; m < mapHeight; m++) {
    auto row = std::vector<int>(mapWidth, 0);
    worldMap.push_back(row);
  }

  for (int k = 0; k < mapHeight; k++) {
    worldMap[k][0] = 1;
    worldMap[k][mapWidth - 1] = 1;
  }

  for (int k = 0; k < mapWidth; k++) {
    worldMap[0][k] = 1;
    worldMap[mapHeight - 1][k] = 1;
  }
}

Game::~Game() {
  std::cout << "Freeing resources.." << std::endl;

  delete[] pixels;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::drawVerticalLine(int x, int yTop, int yBottom, int topColor, int fillColor,
                            int bottomColor) {
  yTop = clamp(yTop, 0, SCREEN_HEIGHT - 1);
  yBottom = clamp(yBottom, 0, SCREEN_HEIGHT - 1);

  if (yBottom == yTop) {
    pixels[yTop * SCREEN_WIDTH + x] = fillColor;
  } else if (yBottom > yTop) {
    pixels[yTop * SCREEN_WIDTH + x] = topColor;
    for (int y = yTop + 1; y < yBottom; ++y) {
      pixels[y * SCREEN_WIDTH + x] = fillColor;
    }
    pixels[yBottom * SCREEN_WIDTH + x] = bottomColor;
  }
}

void Game::drawVerticalLine(int x, int yTop, int yBottom, int color) {
  drawVerticalLine(x, yTop, yBottom, color, color, color);
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

  window = SDL_CreateWindow("Shooter Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
                              SCREEN_WIDTH, SCREEN_HEIGHT);
  pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

  memset(pixels, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}

Uint32 Game::colorAt(int x, int y) {
  // choose wall color
  switch (worldMap[x][y]) {
    case 1:
      return Red;
    case 2:
      return Green;
    case 3:
      return Blue;
    case 4:
      return Turquoise;
    default:
      return Yellow;
  }
}

void Game::run() {
  bool leftMouseButtonDown = false;
  bool quit = false;
  SDL_Event event;

  int drawValue = 0;
  int width = 10;

  Vec2f cameraPlane(0, 1);
  Vec2f viewDirection(-1, 0);
  Vec2f position(22, 12);

  // speed modifiers
  double fps = 60 / 1000.0;  // assumption: 60 ms per frame

  double moveSpeed = fps * 5.0;  // squares per second
  double rotSpeed = fps * 3.0;   // radians per second

  while (!quit) {
    SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_WaitEvent(&event);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
      // calculate ray position and direction
      // x-coordinate in camera space
      double cameraX = 2 * x / double(SCREEN_WIDTH) - 1;

      double rayDirX = viewDirection.x + cameraPlane.x * cameraX;
      double rayDirY = viewDirection.y + cameraPlane.y * cameraX;

      // distance between ray's start position and first-side
      // deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      // which can be simplfied to:
      double deltaDistX = std::abs(1 / rayDirX);
      double deltaDistY = std::abs(1 / rayDirY);

      // what direction to step in x or y-direction (either +1 or -1)
      int stepX = 0;
      int stepY = 0;

      // the current grid location in the map at which the ray is in
      int mapX = int(position.x);
      int mapY = int(position.y);

      // length of ray from current position to next x- / y-side
      double sideDistX = 0;
      double sideDistY = 0;

      // calculate step and initial sideDist
      if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (position.x - mapX) * deltaDistX;
      } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - position.x) * deltaDistX;
      }

      if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (position.y - mapY) * deltaDistY;
      } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - position.y) * deltaDistY;
      }

      // was there a wall hit?
      bool hasHitWall = false;

      // was a NS or a EW wall hit?
      bool hitBoundary = false;

      // perform DDA: jumps one square per iteration (either along x or y direction)
      // See: https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
      while (!hasHitWall) {
        // jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY) {
          sideDistX += deltaDistX;
          mapX += stepX;
          hitBoundary = false;
        } else {
          sideDistY += deltaDistY;
          mapY += stepY;
          hitBoundary = true;
        }

        // Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) {
          hasHitWall = true;
        }
      }

      // Calculate distance projected on camera direction (Euclidean distance will give fisheye
      // effect!)
      double perpWallDist = 0;
      if (!hitBoundary) {
        perpWallDist = (mapX - position.x + 0.5 * (1 - stepX)) / rayDirX;
      } else {
        perpWallDist = (mapY - position.y + 0.5 * (1 - stepY)) / rayDirY;
      }

      // Calculate height of line to draw on screen
      int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

      // calculate lowest and highest pixel to fill in current stripe
      int drawStart = 0.5 * (SCREEN_HEIGHT - lineHeight);
      if (drawStart < 0) {
        drawStart = 0;
      }

      int drawEnd = 0.5 * (lineHeight + SCREEN_HEIGHT);
      if (drawEnd >= SCREEN_HEIGHT) {
        drawEnd = SCREEN_HEIGHT - 1;
      }

      Uint32 color = colorAt(mapX, mapY);

      // give x and y sides different brightness
      if (hitBoundary) {
        color *= 0.5;
      }
      // draw the pixels of the stripe as a vertical line
      drawVerticalLine(x, 0, SCREEN_HEIGHT, White);
      drawVerticalLine(x, drawStart, drawEnd, color);
    }

    switch (event.type) {
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_w:
            if (!hitWall(position.x + viewDirection.x * moveSpeed, position.y)) {
              // new_position += velocity * viewing_direction
              position.x += viewDirection.x * moveSpeed;
            }

            if (!hitWall(position.x, position.y + viewDirection.y * moveSpeed)) {
              position.y += viewDirection.y * moveSpeed;
            }

            break;
          case SDLK_s:
            if (!hitWall(position.x - viewDirection.x * moveSpeed, position.y)) {
              position.x -= viewDirection.x * moveSpeed;
            }

            if (!hitWall(position.x, position.y - viewDirection.y * moveSpeed)) {
              position.y -= viewDirection.y * moveSpeed;
            }
            break;
          case SDLK_a:
            viewDirection.rotate(rotSpeed);
            cameraPlane.rotate(rotSpeed);
            break;

          case SDLK_d:
            viewDirection.rotate(-rotSpeed);
            cameraPlane.rotate(-rotSpeed);
            break;
        }

      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          leftMouseButtonDown = false;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          leftMouseButtonDown = true;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          drawValue += 32 % 256;
        }
        break;
      case SDL_MOUSEMOTION:
        if (leftMouseButtonDown) {
          int mouseX = event.motion.x;
          int mouseY = event.motion.y;
          for (int x = mouseX - width; x < mouseX + width; x++) {
            for (int y = mouseY - width; y < mouseY + width; y++) {
              pixels[y * SCREEN_WIDTH + x] = drawValue;
            }
          }
        }
        break;
      case SDL_QUIT:
        quit = true;
        break;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

bool Game::hitWall(int x, int y) { return worldMap[x][y] != 0; }

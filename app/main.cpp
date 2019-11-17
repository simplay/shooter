#include <memory>
#include "cxxopts.hpp"
#include "exampleConfig.h"
#include "game.h"
#include "logger.h"

int main(int argc, char *argv[]) {
  std::ostringstream oss;
  oss << "Shooter Demo " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << std::endl;

  Logger().log(oss.str());

  std::shared_ptr<Game> game(new Game());

  if (!game->init()) {
    Logger().log("Could not initialize the game");
  }

  game->run();

  return 0;
}

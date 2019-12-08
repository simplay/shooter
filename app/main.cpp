#include <memory>
#include "cxxopts.hpp"
#include "exampleConfig.h"
#include "game.h"
#include "logger.h"
#include "maze_builder.h"

cxxopts::ParseResult parse(int argc, char* argv[]) {
  // clang-format off
  try {
    cxxopts::Options options(argv[0], "For example: ./main.x -w 30 -h 24");

    options
      .allow_unrecognised_options()
      .add_options()
      ("w, width", "World map width", cxxopts::value<int>()->default_value("0"))
      ("h, height", "World map height", cxxopts::value<int>()->default_value("0"))
      ("help", "Print this help message")
      ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException& e) {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }
  // clang-format off
}

int main(int argc, char *argv[]) {
  std::ostringstream oss;
  oss << "Shooter Demo " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << std::endl;

  Logger().log(oss.str());
  auto result = parse(argc, argv);

  int width = result["w"].as<int>();
  int height = result["h"].as<int>();

  oss << "Rendering " << width << "x" << height << std::endl;
  Logger().log(oss.str());

  std::shared_ptr<Game> game(width > 0 && height > 0 ? new Game(width, height) : new Game());

  if (!game->init()) {
    Logger().log("Could not initialize the game");
  } else {
    game->run();
  }

  return 0;
}

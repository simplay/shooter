#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Logger {
 public:
  std::string static toString(const std::string&);

  template <typename Loggable>
  inline void log(const Loggable& l) {
    std::cout << toString(l);
  }
};
#endif

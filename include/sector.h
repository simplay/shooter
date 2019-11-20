#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include "vec2f.h"

class Sector {
 public:
  float floor;
  float ceil;
  const std::vector<Vec2f>& vertices;

  Sector(float floor, float ceil, std::vector<Vec2f>& vertices);
};
#endif

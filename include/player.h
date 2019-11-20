#ifndef PLAYER_H
#define PLAYER_H

#include "vec3f.h"

class Player {
 public:
  Vec3f& position;
  Vec3f& velocity;

  Player(Vec3f& position, Vec3f& velocity);
};
#endif

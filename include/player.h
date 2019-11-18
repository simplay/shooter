#include "vec3f.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player {
 public:
  Vec3f& position;
  Vec3f& velocity;

  Player(Vec3f& position, Vec3f& velocity);
};
#endif

#include "sector.h"

Sector::Sector(float floor, float ceil, std::vector<Vec2f>& vertices)
    : floor(floor), ceil(ceil), vertices(vertices) {}

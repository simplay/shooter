#include "vec2f.h"
#include "SDL.h"

Vec2f::Vec2f(float x, float y) : x(x), y(y) {}

/**
 *  Applies the 2D rotation matrix (results in a cc-rotation)
 *
 *  R = [cos(angle) -sin(angle);
 *       sin(angle)  cos(angle)]
 *
 *  to this vector: R * this
 */
void Vec2f::rotate(float angle) {
  float oldX = x;

  x = oldX * cos(angle) - y * sin(angle);
  y = oldX * sin(angle) + y * cos(angle);
}

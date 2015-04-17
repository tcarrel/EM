#include"pch.h"

#define PI 3.14159265f
#define GRAVITY_CONST 0.0006f
#define MOUSE_MASS 50.0f
#include<cmath>
using std::sqrt;
using std::atan2;
using std::cos;
using std::abs;

#define X_AXIS 'X'
#define Y_AXIS 'Y'

// Project [a1, a2] onto [b1, b2]
float scalar_proj(float a1, float a2, float b1, float b2)
{
  float b_length = sqrt((b1 * b1) + (b2 * b2));

  if (b_length == 0)
    return 0.0f;

  float dot_ab = (a1 * b1) + (a2 * b2);
  
  return dot_ab / b_length;
}

void Particle::init(float xp, float yp, float xv, float yv, int m, float c[])
{
  state_.live.x_position = xp;
  state_.live.y_position = yp;
  state_.live.x_velocity = xv;
  state_.live.y_velocity = yv;
  state_.live.mass       = m;
  for (int i = 0; i < 4; ++i)
  {
    state_.live.color[i] = c[i];
  }
  draw_ = true;
}

bool Particle::animate(float x, float y)
{
  if (x == 0 && y == 0)
  {
    draw_ = false;
    return true;
  }

  float run = state_.live.x_position - x;
  float rise = state_.live.y_position - y;

  if (rise == 0 && run == 0)
  {
    draw_ = false;
    return true;
  }

  float xv = scalar_proj(
    0.0f,
    state_.live.x_velocity,
    rise,
    run);

  float yv = scalar_proj(
    state_.live.y_velocity,
    0.0f,
    rise,
    run);

  if (xv == 0 && yv == 0)
  {
    draw_ = false;
    return true;
  }

  state_.live.x_position -= xv;
  state_.live.y_position -= yv;

  return false;
}
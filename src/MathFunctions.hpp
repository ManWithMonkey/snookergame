#ifndef __MATHFUNCTIONS_H__
#define __MATHFUNCTIONS_H__

#include "GameUtils.hpp"

#include <math.h>

vec2 Normal(vec2 v);
float Norm(vec2 v);
vec2 UnitVector(vec2 v);

bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2);

float PointPointDistance(vec2 a, vec2 b);
float LinePointDistance(vec2 a, vec2 b, Vec2 p);
float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2);

#endif // __MATHFUNCTIONS_H__
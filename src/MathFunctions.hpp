#ifndef __MATHFUNCTIONS_H__
#define __MATHFUNCTIONS_H__

#include "GameUtils.hpp"

#include <algorithm>

bool AABB(vec2 a1, vec2 b1, vec2 a2, vec2 b2);
bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2);
bool MovingCircleCollidesWithStaticLine(vec2 p, vec2 dp, double r, vec2 a, vec2 b);
bool MovingCirclesCollide(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2);

double PointPointDistance(vec2 a, vec2 b);
double LinePointDistance(vec2 a, vec2 b, vec2 p);
double LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2);

vec2 LineClosestPointFromPoint(vec2 a, vec2 b, vec2 p);
vec2 LineCollisionPoint(vec2 a1, vec2 b1, vec2 a2, vec2 b2);
vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, double r, vec2 a, vec2 b);

double GetCollisionPointMovementScalarNewton(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2);

std::pair<vec2, vec2> GetNewVelocities(vec2 p1, vec2 dp1, double r1, vec2 p2, vec2 dp2, double r2);

#endif // __MATHFUNCTIONS_H__
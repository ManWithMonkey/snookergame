#ifndef __MATHFUNCTIONS_H__
#define __MATHFUNCTIONS_H__

#include "GameUtils.hpp"

#include <math.h>
#include <algorithm>

vec2 Normal(vec2 v);
vec2 NormalUnit(vec2 v);
float Norm(vec2 v);
vec2 UnitVector(vec2 v);
float DotProduct(vec2 a, vec2 b);
float Angle(vec2 v);
vec2 MirrorVectorFromNormal(vec2 v, vec2 n);

bool LineLineCollision(vec2 a1, vec2 b1, vec2 a2, vec2 b2);
bool MovingCircleCollidesWithStaticLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b);

float PointPointDistance(vec2 a, vec2 b);
float LinePointDistance(vec2 a, vec2 b, vec2 p);
float LineLineDistance(vec2 a1, vec2 b1, vec2 a2, vec2 b2);

vec2 LineClosestPointFromPoint(vec2 a, vec2 b, vec2 p);
vec2 LineCollisionPoint(vec2 a1, vec2 b1, vec2 a2, vec2 b2);
vec2 MovingCircleCollisionPointWithLine(vec2 p, vec2 dp, float r, vec2 a, vec2 b);

#endif // __MATHFUNCTIONS_H__
#ifndef __VEC2_H__
#define __VEC2_H__

#define _USE_MATH_DEFINES
#include <math.h>

struct vec2{
    double x, y;

    vec2 operator+(const vec2& rhs) const;
    vec2 operator-(const vec2& rhs) const;
    vec2 operator*(double s) const;
};

vec2 Normal(vec2 v);
vec2 NormalUnit(vec2 v);
double Norm(vec2 v);
vec2 UnitVector(vec2 v);
double DotProduct(vec2 a, vec2 b);
double Angle(vec2 v);
vec2 MirrorVectorFromNormal(vec2 v, vec2 n);
vec2 MakeVector(double angle, double length);

#endif // __VEC2_H__
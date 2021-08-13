#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include "Canvas.hpp"
#include "vec2.hpp"
#include "MathFunctions.hpp"

struct Line{
    vec2 a, b;
};

struct Ball{
    float r;

    vec2 pos;
    vec2 vel;

    // change in position for next iteration
    vec2 dpos; 

    bool active = true;
};

struct Hole{
    vec2 pos;
    float holeRadius;
    float insideRadius;
    float pullStrength;

    bool IsClose(const Ball& ball);
    bool IsInside(const Ball& ball);
};

#endif // __GAMEUTILS_H__
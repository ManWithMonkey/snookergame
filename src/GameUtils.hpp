#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include "Canvas.hpp"
#include "vec2.hpp"

struct Line{
    vec2 a, b;
};

struct Ball{
    vec2 pos;
    float r;

    vec2 vel;
    vec2 dpos; // change in position for next iteration
};

#endif // __GAMEUTILS_H__
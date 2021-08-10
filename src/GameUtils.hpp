#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

#include "NCursesHelper.hpp"
#include "DrawFunctions.hpp"
#include "Canvas.hpp"

struct vec2{
    float x, y;
};

struct Line{
    vec2 a, b;
};

struct Ball{
    vec2 pos;
    float r;

    vec2 vel;
};

#endif // __GAMEUTILS_H__
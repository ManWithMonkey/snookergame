#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "NCursesHelper.hpp"

#include <string>
#include <sstream>
#include <iostream>

struct Canvas{
    int cx, cy;
    int w, h;
    char* data = nullptr;
    char alpha = ' ';

    Canvas(int w, int h, int cx, int cy, std::string str);
};

void DrawCanvas(int x, int y, const Canvas* canvas);

#endif // __CANVAS_H__
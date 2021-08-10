#include "NCursesHelper.hpp"

#include <string>
#include <sstream>
#include <iostream>

// void PlotPixel(int x, int y, char c);
void DrawSolidBall(float x, float y, float r, char c);

void BouncingBallTest();

struct Canvas{
    int cx, cy;
    int w, h;
    char* data = nullptr;
    char alpha = ' ';

    Canvas(int w, int h, int cx, int cy, std::string str);
};

void DrawCanvas(int x, int y, const Canvas* canvas);

void CanvasTest();

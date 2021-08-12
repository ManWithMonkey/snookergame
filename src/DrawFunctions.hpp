#ifndef __DRAWFUNCTIONS_H__
#define __DRAWFUNCTIONS_H__

#include "NCursesHelper.hpp"

namespace DrawFunctions{

void PlotPixel(int x, int y, char c);

void DrawLine(float x1, float y1, float x2, float y2, char c);
void DrawLineHorisontal(float y, float x1, float x2, char c);
void DrawLineVertical(float x, float y1, float y2, char c);

void DrawSolidBall(float x, float y, float r, char c);

void PaintDefaultScreen();
void PaintBlankScreen();

};

#endif // __DRAWFUNCTIONS_H__
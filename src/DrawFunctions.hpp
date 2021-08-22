#ifndef __DRAWFUNCTIONS_H__
#define __DRAWFUNCTIONS_H__

#include "NCursesHelper.hpp"

namespace DrawFunctions{

void DrawPoint(float x1, float y1, char c);
void DrawLine(float x1, float y1, float x2, float y2, char c);
void DrawLineHorisontal(float y, float x1, float x2, char c);
void DrawLineVertical(float x, float y1, float y2, char c);

void DrawRectangle(int x1, int y1, int x2, int y2, char c);
void FillRectangle(int x1, int y1, int x2, int y2, char c);

void DrawSolidEllipse(float x, float y, float rx, float ry, char c);

void TypeString(int x, int y, std::string str);

void PaintBlankScreen(Color color);

};

#endif // __DRAWFUNCTIONS_H__
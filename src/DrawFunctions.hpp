#ifndef __DRAWFUNCTIONS_H__
#define __DRAWFUNCTIONS_H__

#include "NCursesHelper.hpp"

namespace DrawFunctions{

void DrawPoint(double x1, double y1, char c);
void DrawLine(double x1, double y1, double x2, double y2, char c);
void DrawLineHorisontal(double y, double x1, double x2, char c);
void DrawLineVertical(double x, double y1, double y2, char c);

void DrawSolidBall(double x, double y, double r, char c);
void DrawSolidEllipse(double x, double y, double rx, double ry, char c);

void DrawRotatedRect(double x, double y, double cx, double cy, double w, double h, char c);

void TypeString(int x, int y, std::string str);

};

#endif // __DRAWFUNCTIONS_H__
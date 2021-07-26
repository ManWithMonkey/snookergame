#ifndef __NCURSESWRAPPER_H__
#define __NCURSESWRAPPER_H__

#include <ncurses.h>
#include <math.h>
#include <algorithm> //std::swap

// Forms color pair, e.g. FG_BG(COLOR_WHITE, COLOR_BLACK)
#define FG_BG(FG, BG) ((FG) + (BG) * 8)

// Get foreground or background color from a pair
#define GET_FG(COLOR) (COLOR % 8)
#define GET_BG(COLOR) (COLOR / 8)

void InitNCurses();
void QuitNCurses();

void Clear(char pixel, int color);
void Render();


void SetPixel(int x, int y, char pixel);
void SetPixel(int x, int y, char pixel, int color);


void MakeBellSound();

void DrawCircleOutline(double x, double y, double radius, int color);
void DrawLine(double x1, double y1, double x2, double y2, char pixel, int color);
void DrawSphere(double x, double y, double r, char pixel, int color);

#endif // __NCURSESWRAPPER_H__
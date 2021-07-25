#ifndef __CONSOLEPANEL_H__
#define __CONSOLEPANEL_H__

#include <algorithm>
#include <cstring>
#include <iostream>
#include <math.h>

#include "ANSI-color-codes.h"
#include "ColorCanvas.h"


// these are homeless
const char luminosityString[] = " .-~^*:;!xb(){}[]?XB&%#";

char GetLuminosityCharacter(double luminosity);
double GetLuminosityFromCharacter(char c);
// 


struct ConsolePanel
{
	int x, y;
	int width, height;
	ColorCanvas canvas;

	ConsolePanel(int x, int y, int w, int h);
	~ConsolePanel();

	void Clear();

	const char* GetPaint(int x, int y) const;
	char GetPixel(int x, int y) const;

	void MakeBellSound();

	void PlotPixel(int x, int y, char pixel, COLOR color = nullptr);
	bool PlotPixelIfBrighter(int x, int y, double luminosity, COLOR color = nullptr);
	void DrawSphere(double x, double y, double r, COLOR color = nullptr);
	void DrawCircleOutline(double x, double y, double r, COLOR color = nullptr);

	// wrappers
	// void PlotPixel(Vec2d p, char pixel);
	// bool PlotPixelIfBrighter(Vec2d p, double luminosity);
	// void DrawSphere(Vec2d p, double r, COLOR color = nullptr);
	// void DrawCircleOutline(Vec2d p, double r);
};

#endif // __CONSOLEPANEL_H__
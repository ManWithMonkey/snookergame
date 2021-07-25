#ifndef __NCURSESWRAPPER_H__
#define __NCURSESWRAPPER_H__

#include <ncurses.h>
#include <math.h>
#include <algorithm> //std::swap

static int CONSOLE_WIDTH, CONSOLE_HEIGHT; // should be constants

void InitNCurses(int w, int h);
void QuitNCurses();

void Clear(char pixel);

void SetPixel(int x, int y, char pixel);

void Render();

// void MakeBellSound();

// void ConsolePanel::MakeBellSound()
// {
// 	// system("echo -ne \007");
// 	system("echo \007");
// }

void DrawCircleOutline(double x, double y, double radius);

void DrawLine(double x1, double y1, double x2, double y2, char pixel = '#');

// void ConsolePanel::DrawSphere(double x, double y, double r, COLOR color)
// {
// 	double cx = (int)(x);
// 	double cy = (int)(y);

// 	for (double ix = -r; ix <= r; ix += 1.0) {
// 		for (double iy = -r; iy <= r; iy += 1.0) {

// 			double distance = std::hypot(cx + ix - x, cy + iy - y);
// 			double luminosity = 1.0 - distance / r;

// 			int sx = cx + ix;
// 			int sy = cy + iy;

// 			if(PlotPixelIfBrighter(sx, sy, luminosity) && color != nullptr){
// 				canvas.ChangeColor(sx, sy, color);
// 			}
// 		}
// 	}
// }


// void ConsolePanel::DrawLine(double x1, double y1, double x2, double y2, PIXEL pixel, COLOR color) 
// {
// 	if(y2 < y1){
// 		std::swap(y1, y2);
// 		std::swap(x1, x2);
// 	}

// 	double dx = x2 - x1;
// 	double dy = y2 - y1;

// 	if(dx == 0){
// 		for(int y = y1; y < y2; y++){
// 			PlotPixel(x1, y, pixel);
// 		}
// 		return;
// 	}

// 	double stepx = (dx > 0 ? 1.0 : -1.0);

// 	// y = kx + b
// 	double k = dy / dx;
// 	double b = y1 - x1 * k;

// 	// x = (y - b) / k

// 	if(std::abs(dx) >= std::abs(dy)){
// 		if(dx > 0){
// 			for(int x = x1; x < x2; x++){
// 				double y = k * x + b;
// 				PlotPixel(x, y, pixel, color);
// 			}
// 		}
// 		else{
// 			for(int x = x2; x < x1; x++){
// 				double y = k * x + b;
// 				PlotPixel(x, y, pixel, color);
// 			}
// 		}
// 	}
// 	else{
// 		for(int y = y1; y < y2; y++){
// 			double x = (y - b) / k;
// 			PlotPixel(x, y, pixel, color);
// 		}
// 	}
// }

#endif // __NCURSESWRAPPER_H__
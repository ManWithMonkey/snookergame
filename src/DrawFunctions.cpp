#include "DrawFunctions.hpp"

namespace DrawFunctions{

void PlotPixel(int x, int y, char c){
	Terminal::PlotPixel(x, y, c);
}

void DrawLine(float x1, float y1, float x2, float y2, char c){
	if(y2 < y1){
		std::swap(y1, y2);
		std::swap(x1, x2);
	}

	double dx = x2 - x1;
	double dy = y2 - y1;

	if(dx == 0){
		for(int y = y1; y < y2; y++){
			PlotPixel(x1, y, c);
		}
		return;
	}

	// y = kx + b
	double k = dy / dx;
	double b = y1 - x1 * k;

	// x = (y - b) / k
	if(std::abs(dx) >= std::abs(dy)){
		if(dx > 0){
			for(int x = x1; x < x2; x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
		else{
			for(int x = x2; x < x1; x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
	}
	else{
		for(int y = y1; y < y2; y++){
			double x = (y - b) / k;
			PlotPixel(x, y, c);
		}
	}
}


void DrawLineHorisontal(float y, float x1, float x2, char c){
    if(x2 < x1) std::swap(x1, x2);

    for(int x=x1; x<x2; x ++){
        PlotPixel(x, y, c);
    }
}

void DrawLineVertical(float x, float y1, float y2, char c){
    if(y2 < y1) std::swap(y1, y2);

    for(int y=y1; y<y2; y ++){
        PlotPixel(x, y, c);
    }
}


void DrawSolidBall(float x, float y, float r, char c){
    float iy = y - r;
    float ix;

    while(iy <= y + r){
        float hw = std::sqrt(std::abs(r * r - (iy - y) * (iy - y)));

        ix = x - hw;

        while(ix <= x + hw){
            PlotPixel(ix, iy, c);

            ix += 1.f;
        }

        iy += 1.f;
    }
}


void PaintDefaultScreen(){
	int w = std::min(Terminal::WIDTH,   Terminal::MAX_WIDTH);
	int h = std::min(Terminal::HEIGHT,  Terminal::MAX_HEIGHT);

	char b = 176;
	char a[] = {'.', ' ', ' ', ' ', ' '};

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (x == 0 || y == 0 || x == Terminal::WIDTH - 1 || y == Terminal::HEIGHT - 1)
				Terminal::SCREEN_DATA[Terminal::Index(x, y)] = b;
			else
				Terminal::SCREEN_DATA[Terminal::Index(x, y)] = a[(y + x) % sizeof(a)];
		}
	}
}

void PaintBlankScreen(){
	int w = std::min(Terminal::WIDTH,   Terminal::MAX_WIDTH);
	int h = std::min(Terminal::HEIGHT,  Terminal::MAX_HEIGHT);

	char a = ' ';

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Terminal::SCREEN_DATA[Terminal::Index(x, y)] = a;
		}
	}
}


};

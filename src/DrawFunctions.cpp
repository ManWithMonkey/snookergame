#include "DrawFunctions.hpp"

namespace DrawFunctions{

void DrawPoint(float x1, float y1, char c){
	PlotPixel(x1, y1, c);
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
			for(int x = std::max(0.f, x1); x < std::min((float)GetWidth(), x2); x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
		else{
			for(int x = std::max(0.f, x2); x < std::min((float)GetWidth(), x1); x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
	}
	else{
		for(int y = std::max(0.f, y1); y < std::min((float)GetHeight(), y2); y++){
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
	if(!isfinite(x) || !isfinite(y) || !isfinite(r))
		return;

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

void DrawSolidEllipse(float x, float y, float rx, float ry, char c){
	if(!isfinite(x) || !isfinite(y) || !isfinite(rx) || !isfinite(ry))
		return;

    float iy = y - ry;
    float ix;

    while(iy <= y + ry){
        float hw = std::sqrt(std::abs(ry * ry - (iy - y) * (iy - y))) * (rx / ry);

        ix = x - hw;

        while(ix <= x + hw){
            PlotPixel(ix, iy, c);

            ix += 1.f;
        }

        iy += 1.f;
    }
}

void TypeString(int x, int y, std::string str){
	for(int i=0; i<str.length(); i++){
		PlotPixel(x+i, y, str[i]);
	}
}

};

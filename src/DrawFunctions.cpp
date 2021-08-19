#include "DrawFunctions.hpp"

namespace DrawFunctions{

void DrawPoint(double x1, double y1, char c){
	PlotPixel(x1, y1, c);
}

void DrawLine(double x1, double y1, double x2, double y2, char c){
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
			for(int x = std::max(0., x1); x < std::min((double)GetWidth(), x2); x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
		else{
			for(int x = std::max(0., x2); x < std::min((double)GetWidth(), x1); x++){
				double y = k * x + b;
				PlotPixel(x, y, c);
			}
		}
	}
	else{
		for(int y = std::max(0., y1); y < std::min((double)GetHeight(), y2); y++){
			double x = (y - b) / k;
			PlotPixel(x, y, c);
		}
	}
}


void DrawLineHorisontal(double y, double x1, double x2, char c){
    if(x2 < x1) std::swap(x1, x2);

    for(int x=x1; x<x2; x ++){
        PlotPixel(x, y, c);
    }
}

void DrawLineVertical(double x, double y1, double y2, char c){
    if(y2 < y1) std::swap(y1, y2);

    for(int y=y1; y<y2; y ++){
        PlotPixel(x, y, c);
    }
}


void DrawSolidBall(double x, double y, double r, char c){
	if(!isfinite(x) || !isfinite(y) || !isfinite(r))
		return;

    double iy = y - r;
    double ix;

    while(iy <= y + r){
        double hw = std::sqrt(std::abs(r * r - (iy - y) * (iy - y)));

        ix = x - hw;

        while(ix <= x + hw){
            PlotPixel(ix, iy, c);

            ix += 1.;
        }

        iy += 1.;
    }
}

void DrawSolidEllipse(double x, double y, double rx, double ry, char c){
	if(!isfinite(x) || !isfinite(y) || !isfinite(rx) || !isfinite(ry))
		return;

    double iy = y - ry;
    double ix;

    while(iy <= y + ry){
        double hw = std::sqrt(std::abs(ry * ry - (iy - y) * (iy - y))) * (rx / ry);

        ix = x - hw;

        while(ix <= x + hw){
            PlotPixel(ix, iy, c);

            ix += 1.;
        }

        iy += 1.;
    }
}

void DrawRotatedRect(double x, double y, double cx, double cy, double w, double h, char c){
	// todo
}

void TypeString(int x, int y, std::string str){
	for(int i=0; i<str.length(); i++){
		PlotPixel(x+i, y, str[i]);
	}
}

};

#include "DrawFunctions.hpp"

void DrawSolidBall(float x, float y, float r, char c){
    float iy = y - r;
    float ix;

    // for(float i = 0; i < y + r; i += 1.f){
    // }

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

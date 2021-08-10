#include "Canvas.hpp"

Canvas::Canvas(int w, int h, int cx, int cy, std::string str) :
    w(w), h(h), cx(cx), cy(cy)
{
    data = new char[w * h];

    int y = 0;

    std::istringstream ss(str);
    std::string line;
    while(std::getline(ss, line, '\n')){
        for(int x=0; x<w; x++){
            data[y * w + x] = line[x];
        }
        y ++;
    }
}

void DrawCanvas(int x, int y, const Canvas* canvas){
    for(int iy = 0; iy < canvas->h; iy ++){
        for(int ix = 0; ix < canvas->w; ix ++){
            int x2 = ix + x - canvas->cx;
            int y2 = iy + y - canvas->cy;

            char c = canvas->data[iy * canvas->w + ix];

            if(c != canvas->alpha){
                PlotPixel(x2, y2, c);
            }
        }
    }
}
